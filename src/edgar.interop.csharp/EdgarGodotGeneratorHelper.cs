namespace Edgar.Interop.CSharp;

using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;

using Edgar.Geometry;
using Edgar.GraphBasedGenerator.Grid2D;

public unsafe static class EdgarGodotGeneratorHelper
{
    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate void IterLayers_ProceduresDelegate(IntPtr layers_Ptr);

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate void IterLnkBoundary_ProceduresDelegate(int x, int y);

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate void IterDoors_ProceduresDelegate(IntPtr door);

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate void IterDoor_ProceduresDelegate(int x1, int y1, int x2, int y2);

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate void IterLayer_ProceduresDelegate(IntPtr name, IntPtr lnk);

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate void IterNodes_ProceduresDelegate(IntPtr node, int layer, bool is_corridor);

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate void IterEdges_ProceduresDelegate(IntPtr from_node, IntPtr to_node);

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate void FillRoomDelegate(IntPtr result, string room, int posX, int posY, bool is_corridor, string template_name);

    // Use 'normal' instead of 'pinned' as 'pinned' can be troublesome when dealing with object-to-object references
    // We only need to save a unique identifier for C# objects in C++, not the actual address,
    // because we don't need to modify C# objects directly in C++.
    // If such a need arises, modifications can be done through C# functions.
    // The key focus is on referencing rather than direct access (address)
    [UnmanagedCallersOnly(EntryPoint = nameof(csharp_obj_alloc_edgar_godot_generator))]
    public static IntPtr csharp_obj_alloc_edgar_godot_generator(IntPtr nodes_Ptr, IntPtr edges_Ptr, IntPtr layers_Ptr) 
    {
        var obj = get_generator(nodes_Ptr, edges_Ptr, layers_Ptr);
        var handle = GCHandle.Alloc(obj);
        var obj_handle_Ptr = GCHandle.ToIntPtr(handle);
        return obj_handle_Ptr;
    }
    [UnmanagedCallersOnly(EntryPoint = nameof(csharp_obj_edgar_generator_generate))]
    public static void csharp_obj_edgar_generator_generate(IntPtr handle_Ptr, IntPtr rooms_Ptr, IntPtr fill_room_Ptr)
    {
        var action = Marshal.GetDelegateForFunctionPointer<FillRoomDelegate>(fill_room_Ptr);

        var handle = GCHandle.FromIntPtr(handle_Ptr);
        var generator = (GraphBasedGeneratorGrid2D<string>)handle.Target;
        var layout = generator.GenerateLayout();
        
        foreach (var room in layout.Rooms)
        {
            action(rooms_Ptr, room.Room, room.Position.X, room.Position.Y, room.IsCorridor, room.RoomTemplate.Name);
        }
    }
    private static GraphBasedGeneratorGrid2D<string> get_generator(IntPtr nodes_Ptr, IntPtr edges_Ptr, IntPtr layers_Ptr)
    {
        var level_description = new LevelDescriptionGrid2D<string>();

        var layers_count = (int)GlobalHelper.ArrayGetSize(layers_Ptr);
        var layer_templates = new List<List<RoomTemplateGrid2D>>();

        void IterLayers(IntPtr layer)
        {
            var templates = new List<RoomTemplateGrid2D>(layers_count);
            void IterLayer(IntPtr name, IntPtr lnk)
            {
                List<Vector2Int> pts = [];
                GlobalHelper.IterLnkBoundary(lnk, Marshal.GetFunctionPointerForDelegate<IterLnkBoundary_ProceduresDelegate>((x, y) => pts.Add(new(x, y))));
                var boundary = new PolygonGrid2D(pts);

                List<DoorGrid2D> doors_list = [];
                GlobalHelper.IterDoors(lnk, Marshal.GetFunctionPointerForDelegate<IterDoors_ProceduresDelegate>(door => 
                    GlobalHelper.IterDoor(door, Marshal.GetFunctionPointerForDelegate<IterDoor_ProceduresDelegate>((x1, y1, x2, y2)
                        => doors_list.Add(new(new(x1, y1), new(x2, y2)))))));

                var manual_door = new ManualDoorModeGrid2D(doors_list);
                var room_template = new RoomTemplateGrid2D(boundary, manual_door, Marshal.PtrToStringUTF8(name));
                templates.Add(room_template);
            }
            GlobalHelper.IterLayer(layer, Marshal.GetFunctionPointerForDelegate<IterLayer_ProceduresDelegate>(IterLayer));
            layer_templates.Add(templates);
        }

        GlobalHelper.IterLayers(layers_Ptr, Marshal.GetFunctionPointerForDelegate<IterLayers_ProceduresDelegate>(IterLayers));

        GlobalHelper.IterNodes(nodes_Ptr, Marshal.GetFunctionPointerForDelegate<IterNodes_ProceduresDelegate>((node, layer, is_corridor)
            => level_description.AddRoom(Marshal.PtrToStringUTF8(node), new RoomDescriptionGrid2D(is_corridor, layer_templates[layer]))));

        GlobalHelper.IterEdges(edges_Ptr, Marshal.GetFunctionPointerForDelegate<IterEdges_ProceduresDelegate>((from_node, to_node)
            => level_description.AddConnection(Marshal.PtrToStringUTF8(from_node), Marshal.PtrToStringUTF8(to_node))));

        return new GraphBasedGeneratorGrid2D<string>(level_description);
    }
}
