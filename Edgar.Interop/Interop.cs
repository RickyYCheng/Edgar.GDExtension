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
    [UnmanagedCallersOnly(EntryPoint = nameof(alloc_csharp_obj))]
    public static IntPtr alloc_csharp_obj()
    {
        var obj = new object();
        var handle = GCHandle.Alloc(obj, GCHandleType.Pinned);

        return GCHandle.ToIntPtr(handle);
    }
    [UnmanagedCallersOnly(EntryPoint = nameof(free_csharp_obj))]
    public static void free_csharp_obj(IntPtr ptr)
    {
        var handle = GCHandle.FromIntPtr(ptr);
        handle.Free();
    }
    [UnmanagedCallersOnly(EntryPoint = nameof(is_obj_freed))]
    public static bool is_obj_freed(IntPtr ptr)
    {
        var handle = GCHandle.FromIntPtr(ptr);
        var isNull = handle.Target is null;
        return isNull;
    }
}
