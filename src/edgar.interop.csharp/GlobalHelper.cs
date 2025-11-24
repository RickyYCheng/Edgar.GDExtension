namespace Edgar.Interop.CSharp;

using System;
using System.Runtime.InteropServices;

[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
public delegate void GDPrintDelegate(string str);

[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
public delegate long ArrayGetSizeDelegate(IntPtr array);

[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
public delegate void IterLayersDelegate(IntPtr layers, IntPtr csharp_delegate);

[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
public delegate void IterLayerDelegate(IntPtr layer, IntPtr csharp_delegate);

[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
public delegate void IterLnkBoundaryDelegate(IntPtr lnk, IntPtr csharp_delegate);

[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
public delegate void IterDoorsDelegate(IntPtr lnk, IntPtr csharp_delegate);

[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
public delegate void IterDoorDelegate(IntPtr door, IntPtr csharp_delegate);

[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
public delegate void IterNodesDelegate(IntPtr nodes, IntPtr csharp_delegate);

[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
public delegate void IterEdgesDelegate(IntPtr edges, IntPtr csharp_delegate);

[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
public delegate void IterTransformationsDelegate(IntPtr lnk, IntPtr csharp_delegate);

public static partial class GlobalHelper
{
    public static GDPrintDelegate GDPrint { get; private set; }
    public static ArrayGetSizeDelegate ArrayGetSize { get; private set; }
    public static IterLayersDelegate IterLayers { get; private set; }
    public static IterLayerDelegate IterLayer { get; private set; }
    public static IterLnkBoundaryDelegate IterLnkBoundary { get; private set; }
    public static IterDoorsDelegate IterDoors { get; private set; }
    public static IterDoorDelegate IterDoor { get; private set; }
    public static IterNodesDelegate IterNodes { get; private set; }
    public static IterEdgesDelegate IterEdges { get; private set; }
    public static IterTransformationsDelegate IterTransformations { get; private set; }
}

public static unsafe partial class GlobalHelper
{

    [UnmanagedCallersOnly(EntryPoint = nameof(csharp_init_global))]
    public static void csharp_init_global(
        IntPtr gdprint,
        IntPtr arrayGetSize,
        IntPtr iterLayers,
        IntPtr iterLayer,
        IntPtr iterLnkBoundary,
        IntPtr iterDoors,
        IntPtr iterDoor,
        IntPtr iterNodes,
        IntPtr iterEdges,
        IntPtr iterTransformations
    )
    {
        GDPrint = Marshal.GetDelegateForFunctionPointer<GDPrintDelegate>(gdprint);
        ArrayGetSize = Marshal.GetDelegateForFunctionPointer<ArrayGetSizeDelegate>(arrayGetSize);
        IterLayers = Marshal.GetDelegateForFunctionPointer<IterLayersDelegate>(iterLayers);
        IterLayer = Marshal.GetDelegateForFunctionPointer<IterLayerDelegate>(iterLayer);
        IterLnkBoundary = Marshal.GetDelegateForFunctionPointer<IterLnkBoundaryDelegate>(iterLnkBoundary);
        IterDoors = Marshal.GetDelegateForFunctionPointer<IterDoorsDelegate>(iterDoors);
        IterDoor = Marshal.GetDelegateForFunctionPointer<IterDoorDelegate>(iterDoor);
        IterNodes = Marshal.GetDelegateForFunctionPointer<IterNodesDelegate>(iterNodes);
        IterEdges = Marshal.GetDelegateForFunctionPointer<IterEdgesDelegate>(iterEdges);
        IterTransformations = Marshal.GetDelegateForFunctionPointer<IterTransformationsDelegate>(iterTransformations);
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
