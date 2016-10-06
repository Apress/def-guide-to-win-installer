using System;
using System.Management;
using System.Windows.Forms;

namespace RemAd
{
	/// <summary>
	/// Summary description for Class1.
	/// </summary>
	class Class1
	{
		class RemoteStuff
		{
			public RemoteStuff()
			{}
	
			public void WinProd()
			{
				ConnectionOptions coptions = new ConnectionOptions();
				coptions.Username = "Administrator";
				coptions.Password = "jptj23251";
				coptions.Impersonation = ImpersonationLevel.Impersonate;
				string msilocation = @"D:\pdw\trynotepad.msi";
				string remsys = "Cx337250-a";
				ManagementScope scope = new ManagementScope ("\\\\"+remsys+"\\root\\cimv2", coptions);
				try
				{
					scope.Connect();
					ManagementPath mp = new ManagementPath ("Win32_Product");
					ManagementClass mc = new ManagementClass (scope, mp, 
						new ObjectGetOptions(null, new TimeSpan(0,0,0,60, 0), true) );
					object [] args = {msilocation, null};
					object getback = mc.InvokeMethod("Advertise", args);
				}
				catch (Exception e)
				{
					MessageBox.Show (e.Message);
				}
			}
		}


		[STAThread]
		static void Main(string[] args)
		{
			RemoteStuff rs = new RemoteStuff();
			rs.WinProd();
		}
	}
}
