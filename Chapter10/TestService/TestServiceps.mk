
TestServiceps.dll: dlldata.obj TestService_p.obj TestService_i.obj
	link /dll /out:TestServiceps.dll /def:TestServiceps.def /entry:DllMain dlldata.obj TestService_p.obj TestService_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del TestServiceps.dll
	@del TestServiceps.lib
	@del TestServiceps.exp
	@del dlldata.obj
	@del TestService_p.obj
	@del TestService_i.obj
