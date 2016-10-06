option explicit
dim installer, msg
Set installer = CreateObject("WindowsInstaller.Installer")
msg = installer.ProductInfo("{60600409-EA9B-45E9-A468-2C68C8DE70DF}","InstallLocation")
Property("TARGETDIR")=msg
set installer=Nothing
msgbox msg