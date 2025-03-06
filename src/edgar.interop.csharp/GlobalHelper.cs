namespace Edgar.Interop.CSharp;

using System;
using System.Runtime.InteropServices;

public static class GlobalHelper 
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
