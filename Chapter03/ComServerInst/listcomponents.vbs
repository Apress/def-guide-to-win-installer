Option Explicit
Public installer, database, ProductGuid
Const msiOpenDatabaseModeReadOnly     = 0
' Connect to Windows Installer object

Set installer = CreateObject("WindowsInstaller.Installer") : CheckError

' Open database
Dim databasePath:databasePath = ".\Release\ComserverInst.msi"
Set database = installer.OpenDatabase(databasePath, msiOpenDatabaseModeReadOnly) : CheckError
GetProductGuid

ListComponents

'For each component, locate its path on the system
Sub ListComponents
Dim view, record, componid, componpath, componversion, fullmsg
	fullmsg = "Product " & ProductGuid & vbcrlf
	Set view = database.OpenView("SELECT `ComponentId` FROM `Component`") : CheckError
	view.Execute : CheckError
	Do
		Set record = view.Fetch : CheckError
		If record Is Nothing Then Exit Do
		componid = record.StringData(1)
		componpath=""
		componpath = installer.ComponentPath (ProductGuid, componid)
		if componpath <> "" then 
			componversion = installer.FileVersion (componpath, false)
			fullmsg = fullmsg & componpath & " " & componversion & vbcrlf
		end if
	Loop
	msgbox fullmsg
End Sub

Sub GetProductGuid 
Dim view, record
   set view = database.OpenView ("SELECT `Value` FROM `Property` WHERE `Property`.`Property` = 'ProductCode' "): CheckError
   view.Execute : CheckError
   set record = view.Fetch : CheckError
   ProductGuid = record.StringData (1)
end Sub


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
	Msgbox message
	Wscript.Quit 2
End Sub
