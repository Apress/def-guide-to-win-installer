option explicit
public computername, objwmi, coll, prod, msg, fso, a
computername = "."
Set fso = CreateObject("Scripting.FileSystemObject")
Set a = fso.CreateTextFile("listproducts.txt", True)
Set objwmi = GetObject("winmgmts:\\" & computername & "\root\cimv2")
Set coll = objwmi.ExecQuery("Select * from Win32_Product")
For Each prod in coll
     msg = prod.name & " " & prod.version & " " & prod.identifyingnumber
     a.writeline(msg)
Next
