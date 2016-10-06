using System;
using System.Runtime.InteropServices;
using System.Reflection;

namespace PDWClass
{
	[ComVisible(true), GuidAttribute("E51820EA-B647-463D-91FB-80A5AB2A97A0")]
	public interface IDoThis
	{
		string GetAString();
	}
	[ComVisible(true), GuidAttribute("D1D38EB0-0210-479A-B8B5-48ADB897A610")]
	[ProgIdAttribute("PDWClass.Class1")]
	[ClassInterface(ClassInterfaceType.None)] 
	public class Class1 : IDoThis
	{

		public Class1()
		{
		}
		public string GetAString ()
		{

			Module mod = Assembly.GetExecutingAssembly().GetModules()[0];
			return "Here's the string from Verion 2 of " + mod.FullyQualifiedName;
		}
	}
}