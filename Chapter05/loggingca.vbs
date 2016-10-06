option explicit
dim inst, rec
set inst = CreateObject("WindowsInstaller.Installer")
set rec=inst.CreateRecord (2)
rec.StringData(1) = "Logging call from " & property("CustomActionData")
Session.Message &H04000000, rec

