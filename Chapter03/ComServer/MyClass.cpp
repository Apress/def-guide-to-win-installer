// MyClass.cpp : Implementation of CMyClass

#include "stdafx.h"
#include "MyClass.h"


// CMyClass

STDMETHODIMP CMyClass::get_SomeString(LONG InputLong, BSTR* pVal)
{
	CComBSTR whatever ("Some String");
	*pVal = whatever.Detach();

	return S_OK;
}

STDMETHODIMP CMyClass::put_SomeString(LONG InputLong, BSTR newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}
