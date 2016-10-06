Option Explicit
Const msiOpenDatabaseModeTransact     = 1
Const msiViewModifyAssign         = 3
' Connect to Windows Installer object
On Error Resume Next
Dim installer : Set installer = Nothing
Set installer = Wscript.CreateObject("WindowsInstaller.Installer") : CheckError
Dim databasePath:databasePath = "parent.msi"
Dim openMode    :  openMode = msiOpenDatabaseModeTransact
Dim updateMode  : updateMode = msiViewModifyAssign 
Dim importPath  : importPath = "trynotepad.msi"
Dim storageName : storageName = "TryNotepad"

' Open database and create a view on the _Storages table
Dim sqlQuery : sqlQuery = "SELECT `Name`,`Data` FROM _Storages"
Dim database : Set database = installer.OpenDatabase(databasePath, openMode) : CheckError
Dim view     : Set view = database.OpenView(sqlQuery)
Dim record :  Set record = installer.CreateRecord(2)
record.StringData(1) = storageName
view.Execute record : CheckError
record.SetStream 2, importPath : CheckError
view.Modify updateMode, record : CheckError
database.Commit : CheckError
Set view = Nothing
Set database = Nothing
CheckError

Sub CheckError
	Dim message, errRec
	If Err = 0 Then Exit Sub
	message = Err.Source & " " & Hex(Err) & ": " & Err.Description
	If Not installer Is Nothing Then
		Set errRec = installer.LastErrorRecord
		If Not errRec Is Nothing Then message = message & vbNewLine & errRec.FormatText
	End If
	Wscript.Echo message
	Wscript.Quit 2
End Sub
