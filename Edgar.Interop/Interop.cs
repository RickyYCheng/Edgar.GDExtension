namespace Edgar.Interop;

using System;
using System.Runtime.InteropServices;

[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
public delegate void PrintDelegate(string str);

public class Interop
{
    [UnmanagedCallersOnly(EntryPoint = nameof(aotsample_add))]
    public static int aotsample_add(int a, int b)
    {
        return a + b;
    }
    [UnmanagedCallersOnly(EntryPoint = nameof(aotsample_greeting))]
    public static void aotsample_greeting(IntPtr print_ptr)
    {
        var print = Marshal.GetDelegateForFunctionPointer<PrintDelegate>(print_ptr);
        
        print("Hello world from C#!");
    }
}
