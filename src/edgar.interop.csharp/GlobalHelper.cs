namespace Edgar.Interop.CSharp;

using System;
using System.Runtime.InteropServices;

[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
public delegate IntPtr GetHandleFromArrayDelegate(IntPtr array_Ptr, int idx);

public static class GlobalHelper 
{
    public static IntPtr get_handle_from_array_Ptr;
    [UnmanagedCallersOnly(EntryPoint = nameof(csharp_init_global))]
    public static void csharp_init_global(IntPtr get_handle_from_array_Ptr) 
    {
        GlobalHelper.get_handle_from_array_Ptr = get_handle_from_array_Ptr;
    }

    [UnmanagedCallersOnly(EntryPoint = nameof(csharp_obj_free))]
    public static void csharp_obj_free(IntPtr obj_handle_Ptr)
    {
        var handle = GCHandle.FromIntPtr(obj_handle_Ptr);
        handle.Free();
    }
    [UnmanagedCallersOnly(EntryPoint = nameof(csharp_gc_collect))]
    public static void csharp_gc_collect() => GC.Collect();
}
