

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Mon Jul 28 07:00:58 2003
 */
/* Compiler settings for _ComServer.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef ___ComServer_h__
#define ___ComServer_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IMyClass_FWD_DEFINED__
#define __IMyClass_FWD_DEFINED__
typedef interface IMyClass IMyClass;
#endif 	/* __IMyClass_FWD_DEFINED__ */


#ifndef __CMyClass_FWD_DEFINED__
#define __CMyClass_FWD_DEFINED__

#ifdef __cplusplus
typedef class CMyClass CMyClass;
#else
typedef struct CMyClass CMyClass;
#endif /* __cplusplus */

#endif 	/* __CMyClass_FWD_DEFINED__ */


/* header files for imported files */
#include "prsht.h"
#include "mshtml.h"
#include "mshtmhst.h"
#include "exdisp.h"
#include "objsafe.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

#ifndef __IMyClass_INTERFACE_DEFINED__
#define __IMyClass_INTERFACE_DEFINED__

/* interface IMyClass */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMyClass;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FB089D5D-82FD-4AF3-AE7B-A99ED90A2A0A")
    IMyClass : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SomeString( 
            /* [in] */ LONG InputLong,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SomeString( 
            /* [in] */ LONG InputLong,
            /* [in] */ BSTR newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMyClassVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMyClass * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMyClass * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMyClass * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMyClass * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMyClass * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMyClass * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMyClass * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SomeString )( 
            IMyClass * This,
            /* [in] */ LONG InputLong,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SomeString )( 
            IMyClass * This,
            /* [in] */ LONG InputLong,
            /* [in] */ BSTR newVal);
        
        END_INTERFACE
    } IMyClassVtbl;

    interface IMyClass
    {
        CONST_VTBL struct IMyClassVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMyClass_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMyClass_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMyClass_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMyClass_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMyClass_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMyClass_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMyClass_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMyClass_get_SomeString(This,InputLong,pVal)	\
    (This)->lpVtbl -> get_SomeString(This,InputLong,pVal)

#define IMyClass_put_SomeString(This,InputLong,newVal)	\
    (This)->lpVtbl -> put_SomeString(This,InputLong,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMyClass_get_SomeString_Proxy( 
    IMyClass * This,
    /* [in] */ LONG InputLong,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IMyClass_get_SomeString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMyClass_put_SomeString_Proxy( 
    IMyClass * This,
    /* [in] */ LONG InputLong,
    /* [in] */ BSTR newVal);


void __RPC_STUB IMyClass_put_SomeString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMyClass_INTERFACE_DEFINED__ */



#ifndef __ComServer_LIBRARY_DEFINED__
#define __ComServer_LIBRARY_DEFINED__

/* library ComServer */
/* [helpstring][uuid][version] */ 


EXTERN_C const IID LIBID_ComServer;

EXTERN_C const CLSID CLSID_CMyClass;

#ifdef __cplusplus

class DECLSPEC_UUID("554EE55D-9117-4996-BFF4-9E89939288C1")
CMyClass;
#endif
#endif /* __ComServer_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


