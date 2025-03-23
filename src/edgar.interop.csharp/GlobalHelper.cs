namespace Edgar.Interop.CSharp;

using System;
using System.Runtime.InteropServices;

[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
public delegate void GDPrintDelegate(string str);

[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
public delegate IntPtr GetDoorHandleFromDoorArrayDelegate(IntPtr array_Ptr, int idx);

[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
public delegate byte GetByteFromPackedByteArrayDelegate(IntPtr array_Ptr, int idx);

[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
public unsafe delegate void GetVector2FromPackedVector2ArrayDelegate(IntPtr array_Ptr, int idx, float* _out_x, float* _out_y);

[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
public unsafe delegate int GetInt32FromPackedInt32ArrayDelegate(IntPtr array_Ptr, int idx);

[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
public delegate IntPtr GetRoomTemplateHandleFromRoomTemplateArrayDelegate(IntPtr array_Ptr, int idx);

[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
public unsafe delegate IntPtr AddLayoutRoomDelegate(IntPtr rooms_Ptr, char *room, bool is_corridor, int posx, int posy, int transformation, char *room_template);

public static partial class GlobalHelper
{
    public static GDPrintDelegate GDPrint { get; private set; }
    public static GetDoorHandleFromDoorArrayDelegate GetDoorHandleFromDoorArray { get; private set; }
    public static GetByteFromPackedByteArrayDelegate GetByteFromPackedByteArray { get; private set; }
    public static GetVector2FromPackedVector2ArrayDelegate GetVector2FromPackedVector2Array { get; private set; }
    public static GetInt32FromPackedInt32ArrayDelegate GetInt32FromPackedInt32Array { get; private set; }
    public static GetRoomTemplateHandleFromRoomTemplateArrayDelegate GetRoomTemplateHandleFromRoomTemplateArray { get; private set; }
    public static AddLayoutRoomDelegate AddLayoutRoom { get; private set; }
}

public static unsafe partial class GlobalHelper
{

    [UnmanagedCallersOnly(EntryPoint = nameof(csharp_init_global))]
    public static void csharp_init_global(
        IntPtr gdprint,
        IntPtr get_doorhandle_from_door_array,
        IntPtr get_byte_from_packed_byte_array,
        IntPtr get_vector2_from_packed_vector2_array,
        IntPtr get_int32_from_packed_int32_array,
        IntPtr get_room_template_handle_from_room_template_array,
        IntPtr add_layout_room
    )
    {
        GDPrint = Marshal.GetDelegateForFunctionPointer<GDPrintDelegate>(gdprint);
        GetDoorHandleFromDoorArray = Marshal.GetDelegateForFunctionPointer<GetDoorHandleFromDoorArrayDelegate>(get_doorhandle_from_door_array);
        GetByteFromPackedByteArray = Marshal.GetDelegateForFunctionPointer<GetByteFromPackedByteArrayDelegate>(get_byte_from_packed_byte_array);
        GetVector2FromPackedVector2Array = Marshal.GetDelegateForFunctionPointer<GetVector2FromPackedVector2ArrayDelegate>(get_vector2_from_packed_vector2_array);
        GetInt32FromPackedInt32Array = Marshal.GetDelegateForFunctionPointer<GetInt32FromPackedInt32ArrayDelegate>(get_int32_from_packed_int32_array);
        GetRoomTemplateHandleFromRoomTemplateArray = Marshal.GetDelegateForFunctionPointer<GetRoomTemplateHandleFromRoomTemplateArrayDelegate>(get_room_template_handle_from_room_template_array);
        AddLayoutRoom = Marshal.GetDelegateForFunctionPointer<AddLayoutRoomDelegate>(add_layout_room);
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
