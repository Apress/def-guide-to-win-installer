// OpenService.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

int main(int argc, char* argv[])
{
	SC_HANDLE scm  = OpenSCManager (NULL, NULL, SC_MANAGER_ALL_ACCESS | GENERIC_EXECUTE);
	if (scm)
	{
		SC_HANDLE scs = OpenService (scm, "TestService", SERVICE_ALL_ACCESS);
		MessageBox (NULL, "We have the handle", "OpenService", MB_OK);
		CloseServiceHandle (scs);
		CloseServiceHandle (scm);
	}
	return 0;
	// Hust test code to see if OpenProcess results in a service which is unable to be uninstalled
	DWORD Pid = 1724; // This is the process id of  a service
	HANDLE hProcess = OpenProcess (PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, Pid); 
	if (hProcess)
	{
		Sleep (120000);
		CloseHandle (hProcess); 
	}
	return 0;
}

