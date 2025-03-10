﻿namespace Edgar.Interop.CSharp;

using System;
using System.Runtime.InteropServices;
using Edgar.GraphBasedGenerator.Grid2D;

public static class DoorGrid2DHelper
{
    // Use 'normal' instead of 'pinned' as 'pinned' can be troublesome when dealing with object-to-object references
    // We only need to save a unique identifier for C# objects in C++, not the actual address,
    // because we don't need to modify C# objects directly in C++.
    // If such a need arises, modifications can be done through C# functions.
    // The key focus is on referencing rather than direct access (address)
    [UnmanagedCallersOnly(EntryPoint = nameof(csharp_obj_alloc_door_grid_2d))]
    public static IntPtr csharp_obj_alloc_door_grid_2d(int x1, int y1, int x2, int y2) 
    {
        var obj = new DoorGrid2D(new(x1, y1), new(x2, y2));
        var handle = GCHandle.Alloc(obj);
        var obj_handle_Ptr = GCHandle.ToIntPtr(handle);
        return obj_handle_Ptr;
    }
}
