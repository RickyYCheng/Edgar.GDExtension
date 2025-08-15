namespace Edgar.Interop.CSharp;

using System;
using System.Runtime.InteropServices;

[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
public delegate void GDPrintDelegate(string str);

public static partial class GlobalHelper
{
    public static GDPrintDelegate GDPrint { get; private set; }
}

public static unsafe partial class GlobalHelper
{

    [UnmanagedCallersOnly(EntryPoint = nameof(csharp_init_global))]
    public static void csharp_init_global(
        IntPtr gdprint
    )
    {
        GDPrint = Marshal.GetDelegateForFunctionPointer<GDPrintDelegate>(gdprint);
    }
}

public static partial class GlobalHelper 
{
    [UnmanagedCallersOnly(EntryPoint = nameof(csharp_obj_free))]
    public static void csharp_obj_free(IntPtr obj_handle_Ptr)
    {
        var handle = GCHandle.FromIntPtr(obj_handle_Ptr);
        handle.Free();
    }
    
    [UnmanagedCallersOnly(EntryPoint = nameof(csharp_gc_collect))]
    public static void csharp_gc_collect() => GC.Collect();
}
