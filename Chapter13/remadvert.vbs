option explicit
public wloc, winst, remsys, aduser, adpass, wproc, wserv, wcom, wstat, wid

remsys= "Cx337250-a"
aduser= "Administrator"
adpass = "jptj23251"
wcom = "msiexec /jm D:\PDW\Trynotepad.msi"
Set wloc = CreateObject("WbemScripting.SWbemLocator")
set wserv = wloc.ConnectServer (remsys, null, aduser, adpass)
'wserv.Security_.ImpersonationLevel = 3 ' impersonate
set winst = wserv.Get("Win32_Process")
wstat = winst.Create(wcom, null, null, wid)
msgbox "Process id " & wid

