using System;
using System.Reflection;

namespace GACInstall
{
	
	public class MyClass
	{
		public MyClass()
		{
			
		}
		public string SaySomething()
		{
			Module mod = Assembly.GetExecutingAssembly().GetModules()[0];
			return "Here's the string from " + mod.FullyQualifiedName;
		}
	}
}
