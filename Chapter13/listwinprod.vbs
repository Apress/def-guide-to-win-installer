'set  computer name - replace variable with appropriate value
Computer = "."

'obtain collection of Windows Installer packages
Set MSIapps = GetObject("winmgmts:{impersonationLevel=impersonate}!\\" & Computer &_ 
"\root\cimv2").ExecQuery("select * from Win32_Product")

'obtain number of program in collection
AppList = AppList & MSIapps.Count & " MSI packages installed:" & VBCRLF & "------" & VBCRLF

'enumerate the names of the packages in the collection
For each App in MSIapps
	AppList = AppList & App.Name & VBCRLF
Next

'display list of packages
Wscript.Echo AppList
