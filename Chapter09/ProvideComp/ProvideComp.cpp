// ProvideComp.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <strsafe.h>

int _tmain(int argc, _TCHAR* argv[])
{
	TCHAR Comp [] = TEXT("{8D8963CB-E9FC-423C-9D8E-A70182694433}");
	TCHAR Qualif [] = TEXT("en-GB");
	TCHAR Prod [] = TEXT("{FA966279-7BF6-4CB7-9C76-ACC55CA8B50D}");
    UINT res=0;
	TCHAR RetPath [_MAX_PATH+1] = {0};
	DWORD len = sizeof (RetPath)/sizeof(TCHAR);
	res = MsiProvideQualifiedComponentEx(Comp, Qualif, INSTALLMODE_DEFAULT,
		Prod, 0, 0, RetPath,  &len);
	TCHAR thing [500] = {0};
	DWORD tlen = sizeof (thing)/sizeof(TCHAR);
	StringCchPrintf  (thing,tlen, TEXT("Result %d Path %s"), res, RetPath);
	MessageBox (NULL, thing, TEXT("Result"), MB_OK);
	return 0;
}

