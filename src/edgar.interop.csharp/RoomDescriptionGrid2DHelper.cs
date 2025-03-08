namespace Edgar.Interop.CSharp;

using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;
using Edgar.Geometry;
using Edgar.GraphBasedGenerator.Grid2D;

public static unsafe class RoomDescriptionGrid2DHelper
{
    // Use 'normal' instead of 'pinned' as 'pinned' can be troublesome when dealing with object-to-object references
    // We only need to save a unique identifier for C# objects in C++, not the actual address,
    // because we don't need to modify C# objects directly in C++.
    // If such a need arises, modifications can be done through C# functions.
    // The key focus is on referencing rather than direct access (address)
    [UnmanagedCallersOnly(EntryPoint = nameof(csharp_obj_alloc_room_description_grid_2d))]
    public static IntPtr csharp_obj_alloc_room_description_grid_2d(bool is_corridor)
    {
        // var obj = new RoomDescriptionGrid2D(is_corridor != 0, []);
        var obj = new object();
        var handle = GCHandle.Alloc(obj);
        var obj_handle_Ptr = GCHandle.ToIntPtr(handle);
        return obj_handle_Ptr;
    }
}