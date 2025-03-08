namespace Edgar.Interop.CSharp;

using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using Edgar.Geometry;
using Edgar.GraphBasedGenerator.Grid2D;

public static unsafe class LevelDescriptionGrid2DHelper
{
    // Use 'normal' instead of 'pinned' as 'pinned' can be troublesome when dealing with object-to-object references
    // We only need to save a unique identifier for C# objects in C++, not the actual address,
    // because we don't need to modify C# objects directly in C++.
    // If such a need arises, modifications can be done through C# functions.
    // The key focus is on referencing rather than direct access (address)
    [UnmanagedCallersOnly(EntryPoint = nameof(csharp_obj_alloc_level_description_grid_2d))]
    public static IntPtr csharp_obj_alloc_level_description_grid_2d()
    {
        var obj = new LevelDescriptionGrid2D<string>();
        var handle = GCHandle.Alloc(obj);
        var obj_handle_Ptr = GCHandle.ToIntPtr(handle);
        return obj_handle_Ptr;
    }
    [UnmanagedCallersOnly(EntryPoint = nameof(csharp_level_description_grid_2dd_add_room))]
    public static void csharp_level_description_grid_2dd_add_room(IntPtr level_description_Ptr, IntPtr room_name_buffer, int room_name_size, IntPtr room_description_Ptr)
    {
        var level_description = (LevelDescriptionGrid2D<string>)GCHandle.FromIntPtr(level_description_Ptr).Target;
        var room_name_builder = new StringBuilder(room_name_size);
        for (var i = 0; i < room_name_size; i++)
        {
            room_name_builder.Append((char)GlobalHelper.GetByteFromPackedByteArray(room_name_buffer, i));
        }
        var room_name = room_name_builder.ToString();
        var room_description = (RoomDescriptionGrid2D)GCHandle.FromIntPtr(room_description_Ptr).Target;
        level_description.AddRoom(room_name, room_description);
    }

}