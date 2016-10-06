========================================================================
       CONSOLE APPLICATION : RegSpy
========================================================================

Use with caution, understand what the program does, and be sure you understand what the registry entries 
are for. I am not responsible for any problems you may have with this program. This program 
is supplied "as is" with no warranty, implied or otherwise. Use at your own risk. 
=======================================================================

Run this program and pass it the path to a Dll, OCX or EXE COM server as the command line parameter.
It will redirect the COM registration output to HKCU\Software\Substitute\Registry\filename>\HKCR and
...\HKLM.  
 
For a Dll or OCX, it calls DllRegisterServer. For an EXE, it runs it with the -regserver 
command line. 
It works by using the RegOverridePredefKey API, which is only available on Windows 2000 and above. 
This API overrides registry reads and writes, so if the program reads some part of the registry 
and uses it to update something, it won't give you the expected results in the substitute keys. So 
it's not very good for programs that update the Perfmon keys, as an example. It works well for programs
that just dump their COM registration into the registry, and the good part is that it won't affect your 
system because the "real" HKCR entries never get created. 