// COMClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\\COMServer\\_COMServer.h"

int _tmain(int argc, _TCHAR* argv[])
{
	CoInitialize(0);
    HRESULT hr = 0; 
	CLSID cls;
	IMyClass* imc =NULL;
	hr = CLSIDFromProgID (OLESTR("COMServer.MyClass"), &cls);
	if (SUCCEEDED(hr)) 
	{
		hr = CoCreateInstance (cls, NULL, CLSCTX_INPROC_SERVER, __uuidof(IMyClass), (void**)&imc);
		if (SUCCEEDED(hr))
		{	
			CComBSTR mystring;
			hr = imc ->get_SomeString (1, &mystring);
			imc->Release();
			if (SUCCEEDED(hr))
			{
				USES_CONVERSION;
				MessageBox  (NULL, OLE2T(mystring), TEXT("Call Returned"), MB_OK);
			}
		}

	}
	return 0;
}

