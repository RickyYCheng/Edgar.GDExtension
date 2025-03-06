namespace Edgar.Interop;

using System;
using System.Runtime.InteropServices;

[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
public delegate void PrintDelegate(string str);

public class CustomObject
{
    private readonly nint print_Ptr;

    public CustomObject(IntPtr print_Ptr)
    {
        // to see collection: 
        // alloc large memory like this without manually gc
        // System.Collections.Generic.List<long> list = new System.Collections.Generic.List<long>(100000);
        this.print_Ptr = print_Ptr;
        var print = Marshal.GetDelegateForFunctionPointer<PrintDelegate>(print_Ptr);
        print("C#> created");
    }
    ~CustomObject()
    {
        var print = Marshal.GetDelegateForFunctionPointer<PrintDelegate>(print_Ptr);
        print("C#> freed");
    }
}

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
    [UnmanagedCallersOnly(EntryPoint = nameof(alloc_custom_obj))]
    public static IntPtr alloc_custom_obj(IntPtr print_ptr)
    {
        var obj = new CustomObject(print_ptr);
        var handle = GCHandle.Alloc(obj, GCHandleType.Pinned);

        return GCHandle.ToIntPtr(handle);
    }
    [UnmanagedCallersOnly(EntryPoint = nameof(free_custom_obj))]
    public static void free_custom_obj(IntPtr ptr)
    {
        var handle = GCHandle.FromIntPtr(ptr);
        handle.Free();
        // GC.Collect(); // will print "freed" immediately
    }
}
