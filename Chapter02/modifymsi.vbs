Option Explicit

Const msiOpenDatabaseModeReadOnly = 0
Const msiOpenDatabaseModeTransact = 1

Dim fso, afile, ts

Set fso = CreateObject("Scripting.FileSystemObject")
Set afile = fso.GetFile("modify.txt")
set ts = afile.OpenAsTextStream (1, 0)

' Connect to Windows installer object
On Error Resume Next
Dim installer 
Set installer = CreateObject("WindowsInstaller.Installer") : CheckError

Dim database : Set database = installer.OpenDatabase(".\Trynotepad\Release\trynotepad.msi", msiOpenDatabaseModeTransact) : CheckError

' Process SQL statements
Dim thecommand, view
Do 
	thecommand = ts.readline
   	Set view = database.OpenView(thecommand) : CheckError
	view.Execute : CheckError
   	if ts.AtEndofStream then exit do
Loop

set installer=nothing
database.Commit

Sub CheckError
	Dim message, errRec
	If Err = 0 Then Exit Sub
	message = Err.Source & " " & Hex(Err) & ": " & Err.Description & vbcrlf & query
	If Not installer Is Nothing Then
		Set errRec = installer.LastErrorRecord
		If Not errRec Is Nothing Then message = message & vbLf & errRec.FormatText
	End If
	Fail message
End Sub

Sub Fail(message)
	Wscript.Echo message
	Wscript.Quit 2
End Sub
