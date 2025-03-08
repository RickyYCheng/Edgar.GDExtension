namespace Edgar.Interop.CSharp;

using System;
using System.Runtime.InteropServices;
using Edgar.GraphBasedGenerator.Grid2D;


public static unsafe class GraphBasedGeneratorGrid2DHelper
{
    // Use 'normal' instead of 'pinned' as 'pinned' can be troublesome when dealing with object-to-object references
    // We only need to save a unique identifier for C# objects in C++, not the actual address,
    // because we don't need to modify C# objects directly in C++.
    // If such a need arises, modifications can be done through C# functions.
    // The key focus is on referencing rather than direct access (address)
    [UnmanagedCallersOnly(EntryPoint = nameof(csharp_obj_alloc_graph_based_generator_grid_2d))]
    public static IntPtr csharp_obj_alloc_graph_based_generator_grid_2d(IntPtr level_description_handle)
    {
        var level_description = (LevelDescriptionGrid2D<string>)GCHandle.FromIntPtr(level_description_handle).Target;
        var obj = new GraphBasedGeneratorGrid2D<string>(level_description);
        var handle = GCHandle.Alloc(obj);
        var obj_handle_Ptr = GCHandle.ToIntPtr(handle);
        return obj_handle_Ptr;
    }
    [UnmanagedCallersOnly(EntryPoint = nameof(csharp_graph_based_generator_grid_2d_generate_layout))]
    public static void csharp_graph_based_generator_grid_2d_generate_layout(IntPtr generator_handle, IntPtr rooms_Ptr)
    {
        var generator = (GraphBasedGeneratorGrid2D<string>)GCHandle.FromIntPtr(generator_handle).Target;
        var layout = generator.GenerateLayout();
        foreach (var room in layout.Rooms)
        {
            fixed(char *room_ptr = room.Room) 
            {
                GlobalHelper.AddLayoutRoom(rooms_Ptr, room_ptr, room.IsCorridor, room.Position.X, room.Position.Y, (int)room.Transformation);
            }
        }
    }
}
