namespace Edgar.Interop.CSharp;

using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using Edgar.GraphBasedGenerator.Grid2D;

public static class ManualDoorModeGrid2DHelper
{
    // Use 'normal' instead of 'pinned' as 'pinned' can be troublesome when dealing with object-to-object references
    // We only need to save a unique identifier for C# objects in C++, not the actual address,
    // because we don't need to modify C# objects directly in C++.
    // If such a need arises, modifications can be done through C# functions.
    // The key focus is on referencing rather than direct access (address)
    [UnmanagedCallersOnly(EntryPoint = nameof(csharp_obj_alloc_manual_door_mode_grid_2d))]
    public static IntPtr csharp_obj_alloc_manual_door_mode_grid_2d(IntPtr array_Ptr, int size)
    {
        var doors = new List<DoorGrid2D>();
        for (var i = 0; i < size; i++) 
        {
            var door = (DoorGrid2D)GCHandle.FromIntPtr(GlobalHelper.GetHandleFromArray(array_Ptr, i)).Target;
            doors.Add(door);
        }

        var obj = new ManualDoorModeGrid2D(doors);
        var handle = GCHandle.Alloc(obj);
        var obj_handle_Ptr = GCHandle.ToIntPtr(handle);
        return obj_handle_Ptr;
    }
}
