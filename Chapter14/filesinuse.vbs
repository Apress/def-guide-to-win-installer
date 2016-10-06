option explicit
Function DoFilesInUse
dim inst, rec, res
const tryagain=4
const DoExit = 2
const Docontinue =1 
set inst = Session.Installer
set rec=inst.CreateRecord (2)
rec.StringData(1) = "anything "
rec.StringData(2) = "Please use Task Manager to terminate the program " & "MyFile.exe"

Do
res = Session.Message (&H05000000, rec)
' check for the program terminated

loop until res <> tryagain
DoFilesInUse = res
end Function