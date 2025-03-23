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
    public static IntPtr csharp_obj_alloc_level_description_grid_2d(int minimum_room_distance)
    {
        var obj = new LevelDescriptionGrid2D<string>() { MinimumRoomDistance = minimum_room_distance };
        var handle = GCHandle.Alloc(obj);
        var obj_handle_Ptr = GCHandle.ToIntPtr(handle);
        return obj_handle_Ptr;
    }
    [UnmanagedCallersOnly(EntryPoint = nameof(csharp_level_description_grid_2d_add_room))]
    public static void csharp_level_description_grid_2d_add_room(IntPtr level_description_Ptr, IntPtr room, int room_length, IntPtr room_description_Ptr)
    {
        var level_description = (LevelDescriptionGrid2D<string>)GCHandle.FromIntPtr(level_description_Ptr).Target;
        var room_name = Encoding.UTF32.GetString((byte*)room, room_length * 4);
        var room_description = (RoomDescriptionGrid2D)GCHandle.FromIntPtr(room_description_Ptr).Target;
        level_description.AddRoom(room_name, room_description);
    }
    [UnmanagedCallersOnly(EntryPoint = nameof(csharp_level_description_grid_2d_add_connection))]
    public static void csharp_level_description_grid_2d_add_connection(IntPtr level_description_Ptr, IntPtr room1_Ptr, int room1_length, IntPtr room2_Ptr, int room2_length)
    {
        var level_description = (LevelDescriptionGrid2D<string>)GCHandle.FromIntPtr(level_description_Ptr).Target;
        var room1 = Encoding.UTF32.GetString((byte*)room1_Ptr, room1_length * 4);
        var room2 = Encoding.UTF32.GetString((byte*)room2_Ptr, room2_length * 4);
        level_description.AddConnection(room1, room2);
    }
}