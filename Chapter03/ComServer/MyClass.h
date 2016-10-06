// MyClass.h : Declaration of the CMyClass

#pragma once
#include "resource.h"       // main symbols


// IMyClass
[
	object,
	uuid("FB089D5D-82FD-4AF3-AE7B-A99ED90A2A0A"),
	dual,	helpstring("IMyClass Interface"),
	pointer_default(unique)
]
__interface IMyClass : IDispatch
{
	[propget, id(1), helpstring("property SomeString")] HRESULT SomeString([in] LONG InputLong, [out, retval] BSTR* pVal);
	[propput, id(1), helpstring("property SomeString")] HRESULT SomeString([in] LONG InputLong, [in] BSTR newVal);
};



// CMyClass

[
	coclass,
	threading("apartment"),
	vi_progid("ComServer.MyClass"),
	progid("ComServer.MyClass.1"),
	version(1.0),
	uuid("554EE55D-9117-4996-BFF4-9E89939288C1"),
	helpstring("MyClass Class")
]
class ATL_NO_VTABLE CMyClass : 
	public IMyClass
{
public:
	CMyClass()
	{
	}


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}

public:
	STDMETHOD(get_SomeString)(LONG InputLong, BSTR* pVal);
	STDMETHOD(put_SomeString)(LONG InputLong, BSTR newVal);
};

