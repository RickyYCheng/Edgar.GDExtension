namespace Edgar.Interop.CSharp;

using System;
using System.Runtime.InteropServices;

[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
public delegate void GDPrintDelegate(string str);

[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
public delegate IntPtr GetDoorHandleFromDoorArrayDelegate(IntPtr array_Ptr, int idx);

public static partial class GlobalHelper
{
    public static GDPrintDelegate GDPrint => Marshal.GetDelegateForFunctionPointer<GDPrintDelegate>(gdprint_Ptr);
    public static GetDoorHandleFromDoorArrayDelegate GetHandleFromArray => Marshal.GetDelegateForFunctionPointer<GetDoorHandleFromDoorArrayDelegate>(get_doorhandle_from_door_array_Ptr);
}

public static partial class GlobalHelper 
{
    private static IntPtr gdprint_Ptr;
    private static IntPtr get_doorhandle_from_door_array_Ptr;
}

public static partial class GlobalHelper 
{
    [UnmanagedCallersOnly(EntryPoint = nameof(csharp_init_global))]
    public static void csharp_init_global(IntPtr gdprint_Ptr, IntPtr get_doorhandle_from_door_array) 
    {
        GlobalHelper.gdprint_Ptr = gdprint_Ptr;
        GlobalHelper.get_doorhandle_from_door_array_Ptr = get_doorhandle_from_door_array;
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


