option explicit
dim ser
Function ValidateSerial
ser = Property("ProductID")
if ser <> "123-1234567" then 
   msgbox "Please Enter the correct key"
   Property ("VALIDSERIAL") = "0"
   ValidateSerial = 1
else
   Property ("VALIDSERIAL") = "1"
   ValidateSerial = 1
end if
end Function