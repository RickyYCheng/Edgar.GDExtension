namespace Edgar.Interop.CSharp;

using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;
using Edgar.Geometry;
using Edgar.GraphBasedGenerator.Grid2D;

public static unsafe class RoomTemplateGrid2DHelper
{
    // Use 'normal' instead of 'pinned' as 'pinned' can be troublesome when dealing with object-to-object references
    // We only need to save a unique identifier for C# objects in C++, not the actual address,
    // because we don't need to modify C# objects directly in C++.
    // If such a need arises, modifications can be done through C# functions.
    // The key focus is on referencing rather than direct access (address)
    [UnmanagedCallersOnly(EntryPoint = nameof(csharp_obj_alloc_room_template_grid_2d))]
    public static IntPtr csharp_obj_alloc_room_template_grid_2d(
        IntPtr name_buffer, 
        int name_buffer_size,
        IntPtr outline_Ptr,
        int outline_size,
        IntPtr doors_handle
    )
    {
        var gdprint = GlobalHelper.GDPrint;

        var name_builder = new StringBuilder(name_buffer_size);
        var char_getter = GlobalHelper.GetByteFromPackedByteArray;
        for (var i = 0; i < name_buffer_size; i++)
        {
            name_builder.Append((char)char_getter(name_buffer, i));
        }
        var name = name_builder.ToString();

        var outline = new List<Vector2Int>(outline_size);
        var vec_getter = GlobalHelper.GetVector2FromPackedVector2Array;
        for (var i = outline_size - 1; i >= 0; i--)
        {
            float x = 0, y = 0;
            vec_getter(outline_Ptr, i, &x, &y);
            var pt = new Vector2Int((int)x, (int)y);
            outline.Add(pt);
        }

        var doors = (ManualDoorModeGrid2D)GCHandle.FromIntPtr(doors_handle).Target;

        var obj = new RoomTemplateGrid2D(new(outline), doors, name);
        var handle = GCHandle.Alloc(obj);
        var obj_handle_Ptr = GCHandle.ToIntPtr(handle);
        return obj_handle_Ptr;
    }
}
