Imports PDWClass
Imports System.Windows.Forms

Module Module1

    Sub Main()
        Dim MyObj As New PDWClass.Class1
        Dim MyS As String

        MyS = MyObj.GetAString
        MessageBox.Show(MyS)

    End Sub

End Module
