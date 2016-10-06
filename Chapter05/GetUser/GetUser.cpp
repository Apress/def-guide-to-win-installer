// GetUser.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <strsafe.h>

int _tmain(int argc, _TCHAR* argv[])
{
 TCHAR tmp [500] = {0};
 HANDLE hProcess, hAccessToken;
 TCHAR InfoBuffer[20000] = {0};
 PTOKEN_USER ptiUser = NULL; 
 DWORD cbti;
 SID_NAME_USE snu;
 hProcess = GetCurrentProcess();
 BOOL opt = OpenProcessToken(hProcess, TOKEN_READ, &hAccessToken); 
 DWORD gle = GetLastError ();
 CloseHandle (hProcess);
 if (!opt) 
 {
	 // MessageBox calls out of this program are a bad idea - they're here for illustration only. When this 
	 // runs as a CA from the local system account, it's worse. 
	StringCchPrintf (tmp, sizeof(tmp)/sizeof(TCHAR), TEXT("OpenProcessToken returned %d "), gle);
	MessageBox (NULL, tmp, TEXT("Error"),MB_OK | MB_SERVICE_NOTIFICATION);
	return 0;
 }
ptiUser = (PTOKEN_USER) HeapAlloc(GetProcessHeap(), 0, 1000);
BOOL gti = GetTokenInformation(hAccessToken, TokenUser, ptiUser, 1000, &cbti); 
gle = GetLastError();
CloseHandle (hAccessToken);
if (!gti) 
{
	StringCchPrintf (tmp, sizeof(tmp)/sizeof(TCHAR), TEXT("GetTokenInformation  returned %d "), gle);
	MessageBox (NULL, tmp, TEXT("Error"),MB_OK | MB_SERVICE_NOTIFICATION);
	return 0;
}
  // Retrieve user name and domain name based on user's SID.
TCHAR szUser [100] = {0};
DWORD cchuser = sizeof (szUser)/sizeof(TCHAR);
TCHAR szDomain [100] = {0}; 
DWORD cchdom =  sizeof(szDomain)/sizeof(TCHAR);
BOOL lua = LookupAccountSid(NULL, ptiUser->User.Sid, szUser, &cchuser,  szDomain, &cchdom, &snu); 
gle = GetLastError();
if (!lua) 
{
	StringCchPrintf (tmp, sizeof(tmp)/sizeof(TCHAR), TEXT("LookupAccountSID returned %d "), gle);
	MessageBox (NULL, tmp, TEXT("Error"),MB_OK | MB_SERVICE_NOTIFICATION);
	return 0;
}

MessageBox (NULL, szUser, szDomain, MB_OK | MB_SERVICE_NOTIFICATION);
return 0;
 }


