Option Explicit
Dim installer, database

Const msiOpenDatabaseModeReadOnly     = 0

' Connect to Windows Installer object
Set installer = CreateObject("WindowsInstaller.Installer") : CheckError

' Open database
Dim databasePath:databasePath = ".\Trynotepad\Release\trynotepad.msi"
Set database = installer.OpenDatabase(databasePath, msiOpenDatabaseModeReadOnly) : CheckError

ListFiles

' List all files in database
Sub ListFiles
Dim view, record, afile, aversion, fsize, fullmsg
	fullmsg = ""
	Set view = database.OpenView("SELECT `FileName`,`Version`, `FileSize` FROM `File`") : CheckError
	view.Execute : CheckError
	Do
		Set record = view.Fetch 
		If record Is Nothing Then Exit Do
		afile = record.StringData(1)

		aversion = record.stringdata (2) 
		fsize = record.Stringdata (3) 
		fullmsg = fullmsg & afile & " " & aversion & " " & fsize & vbcrlf
	Loop
	msgbox fullmsg
End Sub

Sub CheckError
	Dim message, errRec
	If Err = 0 Then Exit Sub
	message = Err.Source & " " & Hex(Err) & ": " & Err.Description
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
