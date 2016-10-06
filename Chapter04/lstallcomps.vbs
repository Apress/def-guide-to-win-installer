Option Explicit
Public installer, fullmsg, comp, prod, a, fso, pname, ploc, pid, psorce

Set fso = CreateObject("Scripting.FileSystemObject")
Set a = fso.CreateTextFile("components.txt", True)

' Connect to Windows Installer object
Set installer = CreateObject("WindowsInstaller.Installer")
a.writeline ("Products")
on error resume next
For Each prod In installer.products
   pid = installer.productinfo (prod, "ProductID")
   pname = installer.productinfo (prod, "InstalledProductName")
   psorce=installer.productinfo(prod, "InstallSource")
   ploc = installer.productinfo (prod, "InstallLocation")  
   a.writeline (prod & " " & pname & " " & ploc & " " & psorce)  
Next
a.writeline ("Components")
For Each comp In installer.components
   a.writeline (comp)
next

