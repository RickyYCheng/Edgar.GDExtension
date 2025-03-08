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
    public static IntPtr csharp_obj_alloc_room_description_grid_2d(bool is_corridor, IntPtr array_Ptr, int size)
    {
        var room_templates = new List<RoomTemplateGrid2D>(size);
        for (var i = 0; i < size; i++)
        {
            var room_template = (RoomTemplateGrid2D)GCHandle.FromIntPtr(GlobalHelper.GetRoomTemplateHandleFromRoomTemplateArray(array_Ptr, i)).Target;
            room_templates.Add(room_template);
        }

        var obj = new RoomDescriptionGrid2D(is_corridor, room_templates);
        var handle = GCHandle.Alloc(obj);
        var obj_handle_Ptr = GCHandle.ToIntPtr(handle);
        return obj_handle_Ptr;
    }
}