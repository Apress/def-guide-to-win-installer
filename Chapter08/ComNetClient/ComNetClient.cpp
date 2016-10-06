// ComNetClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#import "classlib.tlb" raw_interfaces_only no_namespace

int _tmain(int argc, _TCHAR* argv[])
{
	CoInitialize(0);
    HRESULT hr = 0; 
	CLSID cls;
	CComPtr< IDoThis> idt;
	hr = CLSIDFromProgID (OLESTR("PDWClass.Class1"), &cls);
	if (SUCCEEDED(hr)) 
	{
		hr = CoCreateInstance (cls, NULL, CLSCTX_INPROC_SERVER, __uuidof(IDoThis), (void**)&idt);
		if (SUCCEEDED(hr))
		{	
			CComBSTR mystring;
			hr = idt ->GetAString(&mystring);
			if (SUCCEEDED(hr))
			{
				USES_CONVERSION;
				MessageBox  (NULL, OLE2T(mystring), TEXT("Call Returned"), MB_OK);
				idt.Release();
			}
		}
	}
}

