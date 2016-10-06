using System;
using GACInstall;
using System.Windows.Forms;

namespace ExeWantsGac
{
	/// <summary>
	/// Summary description for Class1.
	/// </summary>
	class Class1
	{
		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main(string[] args)
		{
			GACInstall.MyClass gmc = new GACInstall.MyClass();
			string smc = gmc.SaySomething();
			MessageBox.Show (smc);

		}
	}
}
