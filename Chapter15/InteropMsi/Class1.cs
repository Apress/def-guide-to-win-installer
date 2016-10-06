using System;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using System.Text;
using System.Management;

namespace InteropMsi
{
	public class GetMsiData : IDisposable
	{
		string thepath = null;
		IntPtr dbhandle = IntPtr.Zero;
		public GetMsiData (string package) 
		{
			thepath = package;
			int nres = CallMsi.MsiOpenDatabase (thepath, null, ref dbhandle);	
		}
		~GetMsiData ()
		{
			InternalDispose (false);
		}
		public string DoQuery(string query)
		{
			IntPtr viewhandle = IntPtr.Zero;
			IntPtr nothing = IntPtr.Zero;
			int nres = CallMsi.MsiDatabaseOpenView (dbhandle, query, ref viewhandle);
			nres = CallMsi.MsiViewExecute (viewhandle, nothing);
			IntPtr rechandle = IntPtr.Zero;
			nres = CallMsi.MsiViewFetch (viewhandle, ref rechandle);
			if (0!=nres) // No data 
			{
				CallMsi.MsiCloseHandle(viewhandle);
				return null;
			}
			int outlen = 255;
			StringBuilder outbuff = new StringBuilder(outlen);
			nres = CallMsi.MsiRecordGetString (rechandle, 1,  outbuff, ref outlen);
			int rel = CallMsi.MsiCloseHandle(viewhandle);
			rel = CallMsi.MsiCloseHandle (rechandle);
			if (0!=nres) // No data 
				return null;
			return outbuff.ToString();
		}
		public void InternalDispose(bool disposing)
		{
			CallMsi.MsiCloseHandle (dbhandle);
			dbhandle = IntPtr.Zero;
		}
		public void Dispose()
		{
			InternalDispose (true);
			GC.SuppressFinalize(this);
		}

}
	public class InstallerSearches
	{
		public const string INSTALLPROPERTY_LOCALPACKAGE         = "LocalPackage";
		public const string INSTALLPROPERTY_INSTALLEDPRODUCTNAME = "InstalledProductName";
		public const string INSTALLPROPERTY_VERSIONSTRING        = "VersionString";
		public const string INSTALLPROPERTY_INSTALLDATE          = "InstallDate";

		public InstallerSearches () 
		{
		}
		public void ListProducts ()
		{
			int ix = 0;
			StringBuilder guid = new StringBuilder (64);
			int res=0;
			while ( (res=CallMsi.MsiEnumProducts(ix,  guid)) == 0)
			{
				ix++;
				int len = 512;
				StringBuilder cachedmsi = new StringBuilder(len);
				int getprop = CallMsi.MsiGetProductInfo(guid.ToString(), CallMsi.INSTALLPROPERTY_LOCALPACKAGE, cachedmsi,  ref len);
				if (0==len)
					continue;
				len = 512;
				StringBuilder productname = new StringBuilder (len);
				getprop = CallMsi.MsiGetProductInfo(guid.ToString(),  CallMsi.INSTALLPROPERTY_INSTALLEDPRODUCTNAME, productname, ref len);
				len=50;
				StringBuilder versionstring = new StringBuilder(len);
				getprop = CallMsi.MsiGetProductInfo(guid.ToString(),  CallMsi.INSTALLPROPERTY_VERSIONSTRING, versionstring, ref len);
				len = 50;
				StringBuilder installdate = new StringBuilder (len);
				getprop = CallMsi.MsiGetProductInfo(guid.ToString(),  CallMsi.INSTALLPROPERTY_INSTALLDATE, installdate, ref len);
				GetMsiData mi = new GetMsiData (cachedmsi.ToString());
				string ucode = mi.DoQuery ("SELECT `Value` from `Property` WHERE `Property`.`Property` = 'UpgradeCode' ");
				mi.Dispose();			
			}
		}

	}
	public class WMISearches 
	{
		public WMISearches (){}
		public void WhatProds ()
		{
			string servername ="."; 
			ObjectQuery oq = new ObjectQuery("select * from Win32_Product");
			ManagementScope scope = new ManagementScope("\\\\"+servername+"\\root\\cimv2");
			scope.Connect();
			ManagementObjectSearcher sea = new ManagementObjectSearcher(scope, oq);
			foreach (ManagementObject proc in sea.Get()) 
			{
				Console.WriteLine ("Name {0} Cache {1} Guid {2} Version {3}\n", proc["Name"], proc["PackageCache"],
					proc["IdentifyingNumber"], proc["Version"]);
			}
			Console.ReadLine();
		}
	}
	public class CallMsi
	{
		public const string INSTALLPROPERTY_LOCALPACKAGE         = "LocalPackage";
		public const string INSTALLPROPERTY_INSTALLEDPRODUCTNAME = "InstalledProductName";
		public const string INSTALLPROPERTY_VERSIONSTRING        = "VersionString";
		public const string INSTALLPROPERTY_INSTALLDATE          = "InstallDate";
		// This MsiOpenDatabase signature works only with a filename in "persist"
		[DllImport("msi")]
		public static extern int MsiOpenDatabase (string dbpath, string persist, ref IntPtr msihandle);
		[DllImport("msi")]
		public static extern int MsiDatabaseOpenView(IntPtr handle, string query, ref IntPtr viewhandle);
		[DllImport("msi")]
		public static extern int MsiViewExecute (IntPtr viewhandle, IntPtr recordhandle);
		[DllImport("msi")]
		public static extern int MsiViewFetch (IntPtr viewhandle, ref IntPtr recordhandle);
		[DllImport("msi", CharSet=CharSet.Auto)]
		public static extern int MsiRecordGetString (IntPtr recordhandle, int recno,  
			StringBuilder szbuff, 	ref int len);
		[DllImport("msi")]
		public static extern int MsiCloseHandle (IntPtr handle); 
		[DllImport("msi")]
		public static extern int MsiViewClose  (IntPtr viewhandle); 
		[DllImport("msi", CharSet=CharSet.Auto)]
		public static extern int MsiEnumProducts(int index,   StringBuilder guid);
		[DllImport("msi", CharSet=CharSet.Auto)]
		public static extern int MsiEnumComponents(int index, StringBuilder guid);
		[DllImport("msi", CharSet=CharSet.Auto)]
		public static extern int MsiEnumClients(string compguid, int index,  StringBuilder prodguid);
		[DllImport("msi", CharSet=CharSet.Auto)]
		public static extern int MsiGetComponentPath (string prodguid, string compguid, StringBuilder path, ref int szbuf);
		[DllImport("msi", CharSet=CharSet.Auto)]
		public static extern int MsiProvideQualifiedComponent(string CGuid, string qualif, int installmode, string path, ref int len);
		[DllImport("msi", CharSet=CharSet.Auto)]
		public static extern int MsiGetProductInfo (string guid, string propertyname, StringBuilder retprop, ref int szbuf);
	}
	public class ComponentsAndClients 
	{
		public ComponentsAndClients(){}
		public void ShowCompsAndClients()
		{
			int cix = 0;
			int res=0;
			StringBuilder cguid = new StringBuilder (40);
			while ( (res=CallMsi.MsiEnumComponents(cix,  cguid)) == 0)
			{
				cix++;
				int pix=0;
				int cres=0;
				StringBuilder prodguid = new StringBuilder (40);
				while ( (cres = CallMsi.MsiEnumClients (cguid.ToString(), pix, prodguid)) ==0)
				{
					int plen = 256;
					StringBuilder pname = new StringBuilder (256);
					int pires = CallMsi.MsiGetProductInfo (prodguid.ToString(), CallMsi.INSTALLPROPERTY_INSTALLEDPRODUCTNAME,
						pname, ref plen);
					int len = 512;
					StringBuilder pth = new StringBuilder (len);
					CallMsi.MsiGetComponentPath (prodguid.ToString(), cguid.ToString(), pth, ref len);
					pix++;
				}
			}
		}
	}
	
	class Class1
	{
		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main(string[] args)
		{
			//InstallerSearches iss = new InstallerSearches();
			//iss.ListProducts();
			//ComponentsAndClients cnc = new ComponentsAndClients ();
			//cnc.ShowCompsAndClients();
			WMISearches wmi = new WMISearches ();
			wmi.WhatProds();
		}
	}
}
