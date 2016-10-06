The Projects and Files 
CHAPTER 2
The TryNotepad folder contains a project to install notepad.exe plus a shortcut.

listfiles.vbs is a VBScript to list the files in the TryNotepad MSI file.

Modifymsi.vbs is as VBScript that updates the TryNotepad.msi file, using the SQL
statements in the textfile modify.txt.

CHAPTER 3
COMClient
A C++ COM Client program that uses the server built by the COMServer project. 

COMServer
The COM Server program, exports the SomeString property,
uses accessor functions get_SomeString with C++ clients. In the solution folder
there is also a callcom.vbs program that calls the object's method.

COMServerInst
A Setup&Deployment project to install the COM server. 

COMServerMM
A merge module project containing the COM server.

COMClientServerInst
A deployment project to install the COM client and server.
Note - the MSI file in the project's folder is marked readonly and has been manually updated
with Orca to populate the IsolatedComponents table. 

COMClientServerInstAgain 
Another setup project that installs the same COM server to illustrate side-by-side sharing.
Note - the MSI file in the project's folder is marked readonly and has been manually updated
with Orca to populate the IsolatedComponents table. 

NotepadCom
This project is the TryNotepad setup project using the merge module built with the 
COMServerMM project.

RegSpy
This uses the RegOverridePredefKey API call to spy on the registry entries created by COM 
registration without actually registering the DLL or EXE server. It redirects the registration to
the HKCU\Software\Substitute area of the registry. 

regmon.txt 
The output from Sysinternal's registry monitor showing the registry search through the 
windows installer entries to locate ComServer.dll.

CHAPTER 4
Listallcomps.vbs
A Vbscript that enumerates the products installed on the system and lists all the components.

CHAPTER 5
CaDll 
A C++ custom action DLL project containing custom actions described in the chapter.

GetUser
This builds an executable that displayes the user account it's running with. This is used in 
the text to illustrate custom action behavior.

Parent 
Used in the text to illustrate using Type 7 custom actions. The Parent.msi fle in the 
main project folder has been modified with Orca to have Type 7 and Type 39 custom actions
to install and uninstall the embedded TryNotepad.msi file (also in the main project folder).
SetStream.vbs is the VBScript file that adds TryNotyepad.msi as a storage stream in the parent.

ParentType50 
This is the basis for a setup project that uses a Type 50 custom action to install tryNotepad.msi, in the 
main project folder. ParentType50.msi in the main project folder has been updated with Orca to have
custom actions to install and uninstall TryNotepad.msi. 

CHAPTER 6
TryNotepad
This setup project is designed to perform a minor upgrade of the TryNotepad from Chapter 2. The file 
being updated is SomeTestFile.txt, with an extra line in it. 
There are a couple of VBScript files that show how to get the CustomActionData property and 
the UPGRADINGPRODUCTCODE property. 

complie.log is a log of installing notepad while saying that its version is higher (in the File table)
than the file really is. 

CHAPTER 7
ASPProj is the solution that contains the sample ASP.NET application and the setup project, InstASP
that installs it. 

CHAPTER 8
ClassLib and its solution file contains several projects which show installation of assemblies and 
how to expose a .NET class library to COM clients, and side-by-side installation of versions 1.0.0.0 and 
2.0.0.0. The projects inside the ClassLib solution are: 

ClassLib
The project containing assembly version 1.0.0.0 of the class library. 

ClassLib2
Project contains assembly version 2.0.0.0 of the class library. 

ComNetClient 
A C++ client program that calls a method on COMServer. The project folder contains 
Comnetclient.exe.config to redirect the COM call. 

VBCon
A VB.NET client that uses COMServer ass a .NET class library without COM. 

InstNetApp
The setup project that installs all the above pieces, with the registry entries for COM side-by-side 
using Classlib and ClassLib2 and the client programs that call them. 


GACInstall Solution 
The GACInstall solution contains three projects related to custom actions that use assemblies 
in the GAC. 

GACInstall 
This project builds a class library.

ExeWantsGac
This is a C# program that has a reference to the GACInstall class library. 

IntoGAC
This setup project installs the GACInstall class library into the GAC and calls ExeWantsGAC as a custom
action. It is used in the text to show how to run custom actions that have dependenceies on assemblies 
in the GAC.

CAClassLib
This solution contains an empty class library with an installer class, and the setup project Setup1 in
the same solution calls the installer class's Install method passing TARGETDIR and SourceDir.


CHAPTER 9
The ProvideComp folder has the solution file ProvideComp.sln with two projects. ProvideComp itself is 
a C++ program that uses the MsiProvideQualifiedComponentEx Win32 API, showing how to retrieve files
dynamically at run-time from the installation package. 
InstQualif is the setup project to install it. The MSI file in the main project folder has the PublishComponent
table entries for the example code in ProvideComp.

CHAPTER 10
The TestService solution contains two projects. TestService itself is a Win32 (not .NET) Service program. 
The solution also contains the project OpenService which uses the Services APIs to open a handle to 
TestService and wait with a MessageBox. This can be used to see the effect of in-use Service handles
while the Service itself is being uninstalled or reinstalled. 

InstWin32 is a Visual Studio setup solution that installs the TestService above. The project folder contains InstWin32.msi, 
with the Service tables manually populated to install the Service.

The NetService solution contains NetService, a .NET C# Service project containing .NET installer classes, and the 
SetupNetService project is the setup project that installs it using the installer classes. 

NetWithServiceTable is a setup project that installs the .NET service using Windows Installer Service tables instead
of .NET installer classes.  The project folder contains NetWithServiceTable.msi, which has the ServiceControl and
ServiceInstall tables populated to install the Service.

CHAPTER 11
The CLVer1 solution contains a number of projects related to updating assemblies into the GAC. 
CLVer1 and CLVer2 are two versions of a class library assembly, built as the base version, CLVer1, intended to be 
replaced by a later version, CLVer2. The assemblies are identical except for some code and the AssemblyFileVersion. 

VBClient is a normal .NET client program with a reference to CLVer1. 

InstVer1 is a setup project that installs the base version of CLVer1 into the GAC (look at the SourcePath of CLVer1.dll). 

InstMajor is a setup project that does a major upgrade of InstVer1, using the RemovePreviousVersions property to 
uninstall the older CLVer1 and replace it with CLVer2. The project folder contains upgrade.log, a Windows Installer log
of the major upgrade with characteristics referred to in the book's text. 

InstMinor is a setp project used to perform various types of minor upgrade of CLVer1. The project folder contains vemus.log, 
the installer log of a REINSTALLMODE=vemus, and vamus.log, a log of REINSTALLMODE=vamus. Assemblyverlie.log is a log
of a minor upgrade with REINSTALLMODE=vomus but using assembly version lying to replace the assembly in the GAC. 

CHAPTER 12
To show patching, the Base Project folder contains a base version of the TryNotepad MSI package and the Updated Project 
folder contains an updated version of the TryNotepad MSI package. The only difference is that SomeTextFile.txt contains
a few more lines of text. Admin1 and Admin2 contain administrative install images of the base and updated projects.
The main folder contains Notepad.pcp, a patch control file used to generate a patch from the differences between the 
Admin1 and Admin2 packages, base and updated. Notey.log is the output from the MsiMsp.exe patch generation. 
Notepatch.msp is the generated patch file, and Patch.log is the log of the install of its install to patch the base TryNotepad 
installation. 

The Base Project folder also contains a transform example, where the VBScript transform.vbs generates a transform file
of the differences between TryNotepad.msi and ModifiedNotepad.msi, thetransform.mst is the actual transform. 
Product name, ARPCONTACT and Manufacturer were changed wen ModifiedNotepad.msi was made. 

CHAPTER 13 
The MsiStuff solution contains the MsiStuff and Setup.exe projects from the Platform SDK converted to VS 2003. These
tools are used for Internet deployment.

The RemAd project shows how to advertise a product on a remote computer using WMI. 

VBScript to advertise a product remotely. 

CHAPTER 14
Sfc is a program that lists the Windows Protected Files on a system. 

MsiStream is a C++ program to stream data out of the Binary table to a disk file. 

ValidateSerial is the Notepad installation program updated to have a custom action to verify the CD serial key, which
is entered with a new dialog added to the project. The main solution folder contains a copy of the updated MSI file.
 
ValidateSerial.vbs is the VBScript custom action that performs a simple CD serial validation. 

CHAPTER 15 
VBScripts to list products and components on a system.
The InteropMsi solution shows how to call the Win32 MSI APIs from a C# program.



