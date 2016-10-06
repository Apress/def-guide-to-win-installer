option explicit
public computername, objwmi, coll, comp,msg, fso, a
computername = "."
Set fso = CreateObject("Scripting.FileSystemObject")
Set a = fso.CreateTextFile("listcomps.txt", True)
Set objwmi = GetObject("winmgmts:\\" & computername & "\root\cimv2")
Set coll = objwmi.ExecQuery("Select * from Win32_SoftwareElement")
For Each comp in coll
     msg = comp.InstallDate & " " & comp.path & " " & comp.IdentificationCode 
     a.writeline(msg)
Next
