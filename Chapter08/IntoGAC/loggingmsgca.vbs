option explicit
dim inst, rec
msgbox property("CustomActionData")
set inst = CreateObject("WindowsInstaller.Installer")
set rec=inst.CreateRecord (2)
rec.StringData(1) = "Logging call from " & property("CustomActionData")
Session.Message &H04000000, rec

