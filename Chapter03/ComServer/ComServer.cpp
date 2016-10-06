// ComServer.cpp : Implementation of DLL Exports.

#include "stdafx.h"
#include "resource.h"

// The module attribute causes DllMain, DllRegisterServer and DllUnregisterServer to be automatically implemented for you
[ module(dll, uuid = "{2E29D552-34F6-4ED6-B5E1-149F012DFE84}", 
		 name = "ComServer", 
		 helpstring = "ComServer 1.0 Type Library",
		 resource_name = "IDR_COMSERVER") ];
