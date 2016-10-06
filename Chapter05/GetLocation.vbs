option explicit
dim installer, msg
Set installer = CreateObject("WindowsInstaller.Installer")
msg = installer.ProductInfo("{B3E1B56E-D853-4780-BF62-47B95195CD6B}", "InstallLocation")
msgbox msg