using System;
using System.Collections;
using System.ComponentModel;
using System.Configuration.Install;
using System.Text;
using System.Windows.Forms;

namespace CAClassLib
{
	/// <summary>
	/// Summary description for Installer1.
	/// </summary>
	[RunInstaller(true)]
	public class Installer1 : System.Configuration.Install.Installer
	{
		private System.ComponentModel.Container components = null;

		public Installer1()
		{
			// This call is required by the Designer.
			InitializeComponent();

			// TODO: Add any initialization after the InitializeComponent call
		}
		public override void Install(IDictionary savedState)
		{
			base.Install(savedState);
			StringBuilder sb = new StringBuilder();
			foreach (DictionaryEntry de in this.Context.Parameters)
			{
				sb.AppendFormat ("Key = {0},Value = {1}\n", de.Key, de.Value);
			}
			MessageBox.Show(sb.ToString(), "Context Keys and Values");
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


		#region Component Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			components = new System.ComponentModel.Container();
		}
		#endregion
	}
}
