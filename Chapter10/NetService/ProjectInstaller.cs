using System;
using System.Collections;
using System.ComponentModel;
using System.Configuration.Install;
using System.ServiceProcess;
using System.Windows.Forms;
using System.Collections.Specialized;

namespace NetService
{
	/// <summary>
	/// Summary description for ProjectInstaller.
	/// </summary>
	[RunInstaller(true)]
	public class ProjectInstaller : System.Configuration.Install.Installer
	{
		private System.ServiceProcess.ServiceProcessInstaller serviceProcessInstaller1;
		private System.ServiceProcess.ServiceInstaller serviceInstaller1;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public ProjectInstaller()
		{
			// This call is required by the Designer.
			InitializeComponent();

			// TODO: Add any initialization after the InitializeComponent call
		}

		/// <summary> 
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if(components != null)
				{
					components.Dispose();
				}
			}
			base.Dispose( disposing );
		}
		public override void Commit( IDictionary mySavedState )
		{
			base.Commit( mySavedState );
			StringDictionary sd = this.Context.Parameters;
			foreach( DictionaryEntry de in sd)
			{
				MessageBox.Show("Commit:" + de.Key + " = " + de.Value);
			}
		}
		public override void Install( IDictionary mySavedState )
		{
			base.Install( mySavedState );
			StringDictionary sd = this.Context.Parameters;
			foreach( DictionaryEntry de in sd)
			{
				MessageBox.Show("Install: " +de.Key + " = " + de.Value);
			}
		}
		public override void Uninstall( IDictionary mySavedState )
		{
			base.Uninstall( mySavedState );
			StringDictionary sd = this.Context.Parameters;
			foreach( DictionaryEntry de in sd)
			{
				MessageBox.Show("Uninstall: " +de.Key + " = " + de.Value);
			}
		}

		#region Component Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.serviceProcessInstaller1 = new System.ServiceProcess.ServiceProcessInstaller();
			this.serviceInstaller1 = new System.ServiceProcess.ServiceInstaller();
			// 
			// serviceProcessInstaller1
			// 
			this.serviceProcessInstaller1.Account = System.ServiceProcess.ServiceAccount.LocalSystem;
			this.serviceProcessInstaller1.Password = null;
			this.serviceProcessInstaller1.Username = null;
			// 
			// serviceInstaller1
			// 
			this.serviceInstaller1.ServiceName = "Service1";
			// 
			// ProjectInstaller
			// 
			this.Installers.AddRange(new System.Configuration.Install.Installer[] {
																					  this.serviceProcessInstaller1,
																					  this.serviceInstaller1});

		}
		#endregion
	}
}
