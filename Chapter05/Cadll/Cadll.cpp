#include "stdafx.h"
#include <stdio.h>
#include <strsafe.h>
#include <MsiQuery.h>


BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call )
	{
	 case DLL_PROCESS_ATTACH:
			break;
	 case DLL_PROCESS_DETACH:

			break;
	}
	return TRUE;
}
UINT __stdcall RaisePrivilegesSaveReg (MSIHANDLE hInstall)       
{
	// Just here to show that you can't do this from a CA unless you have the required privilege
	// RegSaveKey fails with error 1300 meaning that not all privileges were assigned to the process.
	TCHAR msg [500] = {0};
	HANDLE hToken;
	LUID luid;
	TOKEN_PRIVILEGES tp;
	BOOL res=0;

    res = OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES,
                        &hToken );
	if (!res)
    {
 		StringCchPrintf (msg, sizeof(msg)/sizeof(TCHAR), TEXT("OpenProcessToken failed %d "), GetLastError());
		MessageBox (NULL, msg, TEXT("Error"), MB_OK);		
        return 0;
    }

    res = LookupPrivilegeValue(NULL, SE_BACKUP_NAME, &luid);
	if (!res)
	{
		StringCchPrintf (msg, sizeof(msg)/sizeof(TCHAR), TEXT("LookupPrivilegeValue failed %d "), GetLastError());
		MessageBox (NULL, msg, TEXT("Error"), MB_OK);		
        return 0;
    }

    tp.PrivilegeCount           = 1;
    tp.Privileges[0].Luid       = luid;
    tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    res = AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(TOKEN_PRIVILEGES),
                                NULL, NULL );

	if (!res)
	  {
		StringCchPrintf (msg, sizeof(msg)/sizeof(TCHAR),TEXT("AdjustTokenPrivileges failed %d "), GetLastError());
		MessageBox (NULL, msg, TEXT("Error"), MB_OK);		
        return 0;
	  }
	DeleteFile ("SaveHKCU.rrr");
	long rb = RegSaveKey (HKEY_CURRENT_USER, TEXT("SaveHKCU.rrr"), NULL);
	if (rb!=ERROR_SUCCESS)
	{
		StringCchPrintf (msg, sizeof(msg)/sizeof(TCHAR), TEXT("RegSaveKey failed %d "), rb);
		MessageBox (NULL, msg, TEXT("Error"), MB_OK);		
	}
	else
	{
		MessageBox (NULL, TEXT("Saved the data"), TEXT("No Error"), MB_OK);		
	}
	return 0;
}
UINT LogMessage (MSIHANDLE hInstall, LPCTSTR szMsg)
{
	PMSIHANDLE hRecord = MsiCreateRecord(1);
	MsiRecordSetString(hRecord, 0, szMsg);
    MsiProcessMessage(hInstall, INSTALLMESSAGE(INSTALLMESSAGE_INFO), hRecord);
    return ERROR_SUCCESS; 
}

UINT __stdcall UpgradeList (MSIHANDLE hInstall)       
{
	TCHAR msg[255] = {0};
	UINT nResult = 0;		
	TCHAR Qry [ ] = {TEXT("SELECT `UpgradeCode`,`VersionMin`, `VersionMax` FROM `Upgrade`") };
	PMSIHANDLE hView = 0;    // Class wrapper for MSIHANDLE 
	PMSIHANDLE hDatabase = 0;
	//get the handle to the package
	hDatabase = MsiGetActiveDatabase(hInstall);
	//open it
	nResult = MsiDatabaseOpenView(hDatabase, Qry, &hView);
    if (ERROR_SUCCESS !=nResult )
	{
		StringCchPrintf (msg, sizeof(msg)/sizeof(TCHAR), TEXT("UpgradeList: MsiDatabaseOpenView returned error %d "), nResult);
		LogMessage (hInstall, msg);
		return 0;
	} 
	nResult = MsiViewExecute(hView, NULL);
    if (ERROR_SUCCESS !=nResult )
	{	
		StringCchPrintf (msg,sizeof(msg)/sizeof(TCHAR),TEXT("UpgradeList: MsiViewExecute returned error %d "), nResult);
		LogMessage (hInstall, msg);
		return 0;
	}
	PMSIHANDLE hRec = 0;	
	//retrieves records from the database
	while (ERROR_SUCCESS == (nResult = MsiViewFetch(hView, &hRec) ) )
	{
		TCHAR szCode [100] = {0};
		DWORD codelen = sizeof(szCode)/sizeof(TCHAR);
		UINT getRecord = MsiRecordGetString(hRec, 1, szCode, &codelen);  // UpgradeCode
        if (getRecord != ERROR_SUCCESS)
		{
			StringCchPrintf (msg,sizeof(msg)/sizeof(TCHAR),TEXT("UpgradeList: MsiRecordGetString (1) returned error %d "), getRecord);
			LogMessage (hInstall, msg);
			return 0;
		}
		TCHAR VMinBuff [100] = {0};
		DWORD vminbufflen = sizeof (VMinBuff)/sizeof(TCHAR);
		getRecord = MsiRecordGetString(hRec, 2, VMinBuff, &vminbufflen); 
        if (getRecord != ERROR_SUCCESS)
		{
 			StringCchPrintf (msg,sizeof(msg)/sizeof(TCHAR),TEXT("UpgradeList: MsiRecordGetString (2) returned error %d "), getRecord);
			LogMessage (hInstall, msg);
			return 0;          						
		}
		TCHAR VMaxBuff [100] = {0};
		DWORD vmaxbufflen = sizeof (VMaxBuff)/sizeof(TCHAR);
		getRecord = MsiRecordGetString(hRec, 3, VMaxBuff, &vmaxbufflen); 
		if (getRecord != ERROR_SUCCESS)
		{
 			StringCchPrintf (msg,sizeof(msg)/sizeof(TCHAR),TEXT("UpgradeList: MsiRecordGetString (3) returned error %d "), getRecord);
			LogMessage (hInstall, msg);
			return 0;          						
		}
		StringCchPrintf (msg, sizeof(msg)/sizeof(TCHAR), TEXT("Upgrade:  Code %s VersionMin %s VersionMax %s "),szCode, VMinBuff, VMaxBuff);
		LogMessage (hInstall, msg);
	}
	
    return 0;
}

UINT __stdcall UseCAData (MSIHANDLE hInstall)       
{
	TCHAR vbuff [500] = {0};
	DWORD vlen = sizeof(vbuff)/sizeof(TCHAR);
	UINT gp = MsiGetProperty(hInstall, TEXT("CustomActionData"), vbuff, &vlen);
	TCHAR msg [500] = {0};
	StringCchPrintf (msg, sizeof(msg)/sizeof(TCHAR), TEXT("gp = %d vlen = %d vbuff = %s"), gp, vlen, vbuff );
	MessageBox (NULL, msg, TEXT("Result"), MB_OK);
	return 0;
}
UINT __stdcall ShowFilesInUse (MSIHANDLE hInstall) 
{
	PMSIHANDLE hRec = MsiCreateRecord(4);
	MsiRecordSetString(hRec, 1, TEXT(" "));
	MsiRecordSetString(hRec, 2, TEXT("Please use Task Manager to Terminate these programs:"));
	MsiRecordSetString(hRec, 3, TEXT("someprogram.exe"));
	UINT res = 0;
	do 
	{
	res = MsiProcessMessage(hInstall, INSTALLMESSAGE_FILESINUSE, hRec);
	}
	while (res == IDRETRY);
	if (IDOK==res) // 1 is the Continue button in VS
		return 0;
	if (IDCANCEL ==res) // The Exit button in VS 
		return ERROR_INSTALL_USEREXIT;
	return 0;
}
