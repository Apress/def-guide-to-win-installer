// RegSpy.cpp : Defines the entry point for the console application.
//

// /// DO NOT LINK WITH THE /GZ Option    
#include "stdafx.h"
#include <windows.h>
#include <shlwapi.h>
#include <commdlg.h>

typedef HINSTANCE (WINAPI *ProcLoadLibrary)(char*); 
typedef FARPROC (WINAPI *ProcGetProcAddress)(HMODULE, LPCSTR);
typedef HRESULT (STDAPICALLTYPE *ProcDllReg)() ; 
typedef DWORD  (STDAPICALLTYPE *ProcWaitForS)(HANDLE, DWORD);
typedef long (STDAPICALLTYPE *RegOver) (HKEY, HKEY);
typedef long (STDAPICALLTYPE *RegCreate) (HKEY, LPCTSTR, DWORD, LPTSTR, DWORD, REGSAM, LPSECURITY_ATTRIBUTES, PHKEY, LPDWORD);
typedef DWORD (WINAPI* ProcResume)(HANDLE); 

// Where to redirect registry entries to
char keycr [MAX_PATH] = {"Software\\Substitute\\Registry\\"};
char keylm [MAX_PATH] = {"Software\\Substitute\\Registry\\"};

char shortname [MAX_PATH] = {0};
char comname [MAX_PATH] = {0};
char exeparm [MAX_PATH] = {0};

// The structure we inject into an out of process server to cause it to redirect
typedef struct parmstag {
	char kcr [MAX_PATH];
	char klm [MAX_PATH];
	ProcLoadLibrary	fnload;
	ProcGetProcAddress fnGetProc;
	ProcResume fnResume;
	ProcWaitForS fnWaitFor;
	char advdll [MAX_PATH];
	char regover [MAX_PATH];
	char regcreate [MAX_PATH];
	HANDLE hProcThread;

} myparms;

myparms parms;

#pragma check_stack (off) 
// The injected thread
static DWORD WINAPI ThreadProc (PVOID parm)
{
	HKEY hklm = 0;
	HKEY hkcr = 0;
	DWORD dwr=0;

	myparms* pp = (myparms*)parm;
	// load advapi32.dll 
	HMODULE hadv = pp->fnload (pp->advdll);
	ProcGetProcAddress GetProc = (ProcGetProcAddress)(pp->fnGetProc);
	RegOver RegOverride = (RegOver)GetProc(hadv,pp->regover) ;
	RegCreate RegCreateK = (RegCreate)GetProc(hadv, pp->regcreate ) ;
	// Create our substitute keys 
	long lc = RegCreateK (HKEY_CURRENT_USER, pp->kcr, 0, NULL, 0, KEY_ALL_ACCESS, NULL, &hkcr, &dwr);
	lc = RegOverride (HKEY_CLASSES_ROOT, hkcr);
	lc = RegCreateK(HKEY_CURRENT_USER, pp->klm, 0, NULL, 0, KEY_ALL_ACCESS, NULL, &hklm, &dwr);
	lc = RegOverride(HKEY_LOCAL_MACHINE, hklm);
	// Let the server run and register 
	pp->fnResume (pp->hProcThread); 
	// Wait for the server to finish 
	pp->fnWaitFor (pp->hProcThread, 60000);
	return 0;
}

// This function marks the memory address after ThreadFunc. 

static void AfterThreadProc (void) { }
#pragma check_stack 

void CreateAtlRegistrar ()
{
	// We're going to look for the ATL Registrar in case it's need for our server to register, and if it's there we'll
	// copy the key data to our subsitute HKCR key. 
	HKEY hkatl;
	long lr = RegOpenKeyEx (HKEY_CLASSES_ROOT, "CLSID\\{44EC053A-400F-11D0-9DCD-00A0C90391D3}\\InprocServer32", 0, KEY_READ, &hkatl);
	if (ERROR_FILE_NOT_FOUND==lr){
		MessageBox (NULL, "Unable to find ATL Registrar - Registration Might Fail", "Warning", MB_OK);
	}
	else
	{
		char clsid [MAX_PATH];
		char locatl [MAX_PATH];
		strcpy (clsid, keycr);	// The HKCR substitute
		strcat (clsid, "\\CLSID\\{44EC053A-400F-11D0-9DCD-00A0C90391D3}\\InprocServer32");		
		// We'll assume in here that all the ATL.DLL registry entries are present
		DWORD dwsz = sizeof (locatl);
		DWORD dwt = REG_SZ;
		lr = RegQueryValueEx (hkatl, NULL, NULL, &dwt, (BYTE*)locatl, &dwsz);		// Path to Dll
		HKEY hkclsid;
		DWORD dwr;
		//Write Clsid to our substitute HKCR 
		lr = RegCreateKeyEx (HKEY_CURRENT_USER, clsid, 0, NULL, 0, KEY_ALL_ACCESS, NULL, &hkclsid, &dwr);
		// Set the InprocServer32 key value
		lr = RegSetValueEx (hkclsid, NULL, 0, REG_SZ, (BYTE*)locatl, dwsz);
		//Get and set the ThreadingModel 
		lr = RegQueryValueEx (hkatl, "ThreadingModel", NULL, &dwt, (BYTE*)locatl, &dwsz);
		lr = RegSetValueEx (hkclsid, "ThreadingModel", 0, REG_SZ, (BYTE*)locatl, dwsz);
		RegCloseKey (hkatl);
		RegCloseKey (hkclsid);
	}
}

void DeleteAtlRegistrar ()
{
	char delclsid [MAX_PATH];
	strcpy (delclsid, keycr);
	strcat (delclsid, "\\CLSID\\{44EC053A-400F-11D0-9DCD-00A0C90391D3}");
	SHDeleteKey (HKEY_CURRENT_USER, delclsid);
}

int injectexe(char* parm)
{
	
	// Copy the keys to the structure that we'll send to our remote thread
	strcpy (parms.kcr, keycr);
	strcpy (parms.klm, keylm);

	// GetProcAddress values for the functions that our remote thread will call. 
	HMODULE hk = LoadLibrary ("kernel32.dll");
	parms.fnload = (ProcLoadLibrary)::GetProcAddress (hk, "LoadLibraryA"); 
	parms.fnGetProc = (ProcGetProcAddress)::GetProcAddress (hk, "GetProcAddress");
	parms.fnResume = (ProcResume)::GetProcAddress(hk, "ResumeThread"); 
	parms.fnWaitFor = (ProcWaitForS)::GetProcAddress (hk, "WaitForSingleObject"); 
	strcpy (parms.advdll, "advapi32.dll");

	// The Regxxx functions are in advapi32.dll which we'll load in our remote thread
	strcpy (parms.regcreate, "RegCreateKeyExA");
	strcpy (parms.regover, "RegOverridePredefKey");

	// Build a command line for the server & make sure we can find it and initialize for the remote thread
	char cmdline [MAX_PATH];
	strcpy (cmdline, comname); 

	strcat (cmdline, " ");
	strcat (cmdline, parm);
	// Some ATL servers are services so we may have put -service in the command line, however this will cause
	// a service to be created which RegOverridePredefKey will not circumvent. 
	if (0) // Just a debugging check
	ThreadProc (&parms);	// Jump into it to see it run in our process - Debugging purposes only

	STARTUPINFO si;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	PROCESS_INFORMATION pi;

	void* pcode = 0;
	void* pdata = 0;
	// Cleanup code 
	if (0) 
	{
cleanup:
		if (pcode)
			VirtualFreeEx (pi.hProcess, pcode, 0, MEM_RELEASE);
		if (pdata)
			VirtualFreeEx (pi.hProcess, pdata, 0, MEM_RELEASE);
		TerminateProcess (pi.hProcess, 1);
		WaitForSingleObject (pi.hProcess, INFINITE);
		WaitForSingleObject (pi.hThread, INFINITE);
		return 1;
	}
	// Create the process suspened prior to injecting memory and our code
	BOOL bc = CreateProcess (NULL, cmdline, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi);
	if (!bc)
	{
		MessageBox (NULL, "Can't Create Process", cmdline, MB_OK);
		return 1;
	}
	
	HANDLE hProcThread=0;
	BOOL bdup = DuplicateHandle (GetCurrentProcess(), pi.hThread, pi.hProcess, &hProcThread, PROCESS_ALL_ACCESS, false, 0);
	if (!bdup)
	{
		MessageBox (NULL, "Can't Dup Handle", cmdline, MB_OK);
		goto cleanup;
		return 1;
	}
	parms.hProcThread = hProcThread; 
	// This code does not clean up absoltely everything, relying instead on process termination to
	// clean up handles and memory
	const int cbCodeSize = (BYTE*)AfterThreadProc - (BYTE*)ThreadProc; 

	pcode = VirtualAllocEx (pi.hProcess, 0, cbCodeSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE); 
	// The process was created suspended and has done very little.
	// TerminateProcess is unfriendly but should be safe under these circumstances
	if (0==pcode)
	{
		MessageBox (NULL, "Allocate code memory in process", cmdline, MB_OK);
		goto cleanup;
	}
	pdata = VirtualAllocEx (pi.hProcess, 0, sizeof (parms), MEM_COMMIT, PAGE_EXECUTE_READWRITE); 
	if (0==pdata)
	{
		MessageBox (NULL, "Allocate data memory in process", cmdline, MB_OK);
		goto cleanup;
	}

	DWORD dwr;
	bc = WriteProcessMemory (pi.hProcess, pcode, (LPVOID)(DWORD) ThreadProc, cbCodeSize, &dwr); 
	if (!bc)
	{
		MessageBox (NULL, "Can't Write code to Process Memory", cmdline, MB_OK);
		goto cleanup;
	}

	bc = WriteProcessMemory (pi.hProcess, pdata, &parms, sizeof (parms), &dwr); 
	if (!bc)
	{
		MessageBox (NULL, "Can't Write data to Process Memory", cmdline, MB_OK);
		goto cleanup;
	}

	// At this point in time we're ready to set up the substitute registry entries 
	
	CreateAtlRegistrar();

	// Let the remote injected thread go 
	HANDLE ht = CreateRemoteThread (pi.hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)pcode, pdata, 0, NULL);
	long gle = GetLastError();
	dwr = WaitForSingleObject (pi.hThread, INFINITE);
	CloseHandle (pi.hThread);
	CloseHandle (pi.hProcess);
	WaitForSingleObject (ht, 10000);
	CloseHandle (ht);
	// Delete the ATL Registrar key we put in the substitute 
	DeleteAtlRegistrar();
	return 1;

}
int DoDll()
{
	// We're going to look for the ATL Registrar in case it's need for our server to register, and if it's there we'll
	// copy the key data to our subsitute HKCR key. 
	CreateAtlRegistrar();
	// Load the target library 
	HMODULE hMod = ::LoadLibrary (comname);
	if (NULL==hMod){
		MessageBox (NULL, "Can't Find", comname, MB_OK);		
		return 1;
	}
	HKEY hklm = 0;
	HKEY hkcr = 0;
	DWORD dwr=0;
	// Find DllregisterServer, prepare to call it 
	ProcDllReg DLLRegisterServer = (ProcDllReg)::GetProcAddress(hMod,"DllRegisterServer" ) ;
	if (DLLRegisterServer != NULL)
    {
		long lc = RegCreateKeyEx (HKEY_CURRENT_USER, keycr, 0, NULL, 0, KEY_ALL_ACCESS, NULL, &hkcr, &dwr);
		lc = RegOverridePredefKey (HKEY_CLASSES_ROOT, hkcr);

		lc = RegCreateKeyEx (HKEY_CURRENT_USER, keylm, 0, NULL, 0, KEY_ALL_ACCESS, NULL, &hklm, &dwr);
		lc = RegOverridePredefKey (HKEY_LOCAL_MACHINE, hklm);
		CoInitialize (NULL);	// Someone has to call this prior to using the COM APIs 
		ProcDllReg DLLRegisterServer =
		  (ProcDllReg)::GetProcAddress(hMod,"DllRegisterServer" ) ;
		HRESULT regResult = DLLRegisterServer() ;
		RegOverridePredefKey (HKEY_CLASSES_ROOT, NULL);
		RegOverridePredefKey (HKEY_LOCAL_MACHINE, NULL);
		RegCloseKey (hkcr);
		RegCloseKey (hklm);
	}
	else {
		MessageBox (NULL, "DllRegisterServer Not Exported", comname, MB_OK);
	}
	// Delete the ATL Registrar key we put in the substitute 
	DeleteAtlRegistrar();

	::FreeLibrary (hMod);
	return 1;
}
int main(int argc, char* argv[])
{

	if (argc <=1){
		MessageBox (NULL, "No File Specified in Command Line", "Error", MB_OK);
		return 1;
	}
	// Get path, file name
	strcpy (comname, argv[1]);
	if (argc > 2) 
		strcpy (exeparm, argv[2]);	
	else 
		strcpy (exeparm, "-regserver");
	short stuff = GetFileTitle (comname, shortname, MAX_PATH);
	// Build our substitute registry keys 
	strcat (keycr, shortname);
	strcat (keycr, "\\HKCR");
	strcat (keylm, shortname);
	strcat (keylm, "\\HKLM");

	// Delete them if they exist - start with a clean slate 
	SHDeleteKey (HKEY_CURRENT_USER, keycr);
	SHDeleteKey (HKEY_CURRENT_USER, keylm);

	char *pdest;
	pdest = strstr (comname, ".exe");
	if (pdest!=NULL)
	{
		return injectexe(exeparm);
	}
	else
		return DoDll();


	return 0;
}

