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
    public delegate void FillRoomDelegate(IntPtr result, byte *room, int posX, int posY, bool is_corridor, byte* template_name, int transformation, int *outline_pts, int outline_size, int doors_count, IntPtr doors_from_rooms, IntPtr doors_to_rooms, int *doors_line_data);

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate void IterTransformations_ProceduresDelegate(int transformation);

    // Use 'normal' instead of 'pinned' as 'pinned' can be troublesome when dealing with object-to-object references
    // We only need to save a unique identifier for C# objects in C++, not the actual address,
    // because we don't need to modify C# objects directly in C++.
    // If such a need arises, modifications can be done through C# functions.
    // The key focus is on referencing rather than direct access (address)
    [UnmanagedCallersOnly(EntryPoint = nameof(csharp_obj_alloc_edgar_godot_generator))]
    public static IntPtr csharp_obj_alloc_edgar_godot_generator(IntPtr nodes_Ptr, IntPtr edges_Ptr, IntPtr layers_Ptr, int minimum_room_distance) 
    {
        try
        {
            if (nodes_Ptr == IntPtr.Zero || edges_Ptr == IntPtr.Zero || layers_Ptr == IntPtr.Zero)
            {
                GlobalHelper.GDPrint?.Invoke("[Edgar.GDExtension] csharp_obj_alloc_edgar_godot_generator: null pointer argument");
                return IntPtr.Zero;
            }
            var obj = get_generator(nodes_Ptr, edges_Ptr, layers_Ptr, minimum_room_distance);
            if (obj == null)
            {
                GlobalHelper.GDPrint?.Invoke("[Edgar.GDExtension] csharp_obj_alloc_edgar_godot_generator: failed to create generator");
                return IntPtr.Zero;
            }
            var handle = GCHandle.Alloc(obj);
            var obj_handle_Ptr = GCHandle.ToIntPtr(handle);
            return obj_handle_Ptr;
        }
        catch (Exception ex)
        {
            try { GlobalHelper.GDPrint?.Invoke($"[Edgar.GDExtension] csharp_obj_alloc_edgar_godot_generator failed: {ex.Message}"); } catch { }
            return IntPtr.Zero;
        }
    }
    [UnmanagedCallersOnly(EntryPoint = nameof(csharp_obj_edgar_generator_generate))]
    public static void csharp_obj_edgar_generator_generate(IntPtr handle_Ptr, IntPtr rooms_Ptr, IntPtr fill_room_Ptr)
    {
        try
        {
            if (handle_Ptr == IntPtr.Zero || rooms_Ptr == IntPtr.Zero || fill_room_Ptr == IntPtr.Zero)
            {
                GlobalHelper.GDPrint?.Invoke("[Edgar.GDExtension] csharp_obj_edgar_generator_generate: null pointer argument");
                return;
            }
            var action = Marshal.GetDelegateForFunctionPointer<FillRoomDelegate>(fill_room_Ptr);

            var handle = GCHandle.FromIntPtr(handle_Ptr);
            var generator = (GraphBasedGeneratorGrid2D<string>)handle.Target;
            if (generator == null)
            {
                GlobalHelper.GDPrint?.Invoke("[Edgar.GDExtension] csharp_obj_edgar_generator_generate: generator is null");
                return;
            }
            var layout = generator.GenerateLayout();
            
            foreach (var room in layout.Rooms)
            {
                var outline = room.Outline.GetPoints().SelectMany(p => new int[] { p.X, p.Y }).ToArray();
                var doors = room.Doors;
                var doorsCount = doors.Count;

                var roomBytes = System.Text.Encoding.UTF8.GetBytes((room.Room ?? "") + '\0');
                var templateBytes = System.Text.Encoding.UTF8.GetBytes((room.RoomTemplate?.Name ?? "") + '\0');

                fixed (byte* roomNamePtr = roomBytes)
                fixed (byte* templateNamePtr = templateBytes)
                fixed (int* outline_Ptr = outline)
                {
                    if (doorsCount == 0)
                    {
                        action(rooms_Ptr, roomNamePtr, room.Position.X, room.Position.Y, room.IsCorridor, templateNamePtr, (int)room.Transformation, outline_Ptr, outline.Length, 0, IntPtr.Zero, IntPtr.Zero, null);
                    }
                    else
                    {
                        var fromRoomHandles = new GCHandle[doorsCount];
                        var toRoomHandles = new GCHandle[doorsCount];
                        var fromRoomPtrs = new IntPtr[doorsCount];
                        var toRoomPtrs = new IntPtr[doorsCount];
                        var doorsLineData = new int[doorsCount * 4];

                        try
                        {
                            for (int i = 0; i < doorsCount; i++)
                            {
                                var door = doors[i];

                                var fromBytes = System.Text.Encoding.UTF8.GetBytes(door.FromRoom + '\0');
                                var toBytes = System.Text.Encoding.UTF8.GetBytes(door.ToRoom + '\0');

                                fromRoomHandles[i] = GCHandle.Alloc(fromBytes, GCHandleType.Pinned);
                                toRoomHandles[i] = GCHandle.Alloc(toBytes, GCHandleType.Pinned);

                                fromRoomPtrs[i] = fromRoomHandles[i].AddrOfPinnedObject();
                                toRoomPtrs[i] = toRoomHandles[i].AddrOfPinnedObject();

                                doorsLineData[i * 4 + 0] = door.DoorLine.From.X;
                                doorsLineData[i * 4 + 1] = door.DoorLine.From.Y;
                                doorsLineData[i * 4 + 2] = door.DoorLine.To.X;
                                doorsLineData[i * 4 + 3] = door.DoorLine.To.Y;
                            }

                            var fromRoomArrayHandle = GCHandle.Alloc(fromRoomPtrs, GCHandleType.Pinned);
                            var toRoomArrayHandle = GCHandle.Alloc(toRoomPtrs, GCHandleType.Pinned);

                            fixed (int* doorsLinePtr = doorsLineData)
                            {
                                action(rooms_Ptr, roomNamePtr, room.Position.X, room.Position.Y, room.IsCorridor, templateNamePtr, (int)room.Transformation, outline_Ptr, outline.Length, doorsCount, fromRoomArrayHandle.AddrOfPinnedObject(), toRoomArrayHandle.AddrOfPinnedObject(), doorsLinePtr);
                            }

                            fromRoomArrayHandle.Free();
                            toRoomArrayHandle.Free();
                        }
                        finally
                        {
                            for (int i = 0; i < doorsCount; i++)
                            {
                                if (fromRoomHandles[i].IsAllocated) fromRoomHandles[i].Free();
                                if (toRoomHandles[i].IsAllocated) toRoomHandles[i].Free();
                            }
                        }
                    }
                }
            }
        }
        catch (Exception ex)
        {
            try { GlobalHelper.GDPrint?.Invoke($"[Edgar.GDExtension] csharp_obj_edgar_generator_generate failed: {ex.Message}"); } catch { }
        }
    }
    [UnmanagedCallersOnly(EntryPoint = nameof(csharp_obj_edgar_generator_inject_seed))]
    public static void csharp_obj_edgar_generator_inject_seed(IntPtr handle_Ptr, int seed)
    {
        try
        {
            if (handle_Ptr == IntPtr.Zero)
            {
                GlobalHelper.GDPrint?.Invoke("[Edgar.GDExtension] csharp_obj_edgar_generator_inject_seed: null pointer argument");
                return;
            }
            var handle = GCHandle.FromIntPtr(handle_Ptr);
            var generator = (GraphBasedGeneratorGrid2D<string>)handle.Target;
            if (generator == null)
            {
                GlobalHelper.GDPrint?.Invoke("[Edgar.GDExtension] csharp_obj_edgar_generator_inject_seed: generator is null");
                return;
            }
            generator.InjectRandomGenerator(new(seed));
        }
        catch (Exception ex)
        {
            try { GlobalHelper.GDPrint?.Invoke($"[Edgar.GDExtension] csharp_obj_edgar_generator_inject_seed failed: {ex.Message}"); } catch { }
        }
    }
    private static GraphBasedGeneratorGrid2D<string> get_generator(IntPtr nodes_Ptr, IntPtr edges_Ptr, IntPtr layers_Ptr, int minimum_room_distance)
    {
        var level_description = new LevelDescriptionGrid2D<string>();
        level_description.MinimumRoomDistance = minimum_room_distance;

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

                List<TransformationGrid2D> transformations = null;
                GlobalHelper.IterTransformations(lnk, Marshal.GetFunctionPointerForDelegate<IterTransformations_ProceduresDelegate>(transformation =>
                {
                    transformations ??= [];
                    transformations.Add((TransformationGrid2D)transformation);
                }));

                var manual_door = new ManualDoorModeGrid2D(doors_list);
                var room_template = new RoomTemplateGrid2D(boundary, manual_door, Marshal.PtrToStringUTF8(name), allowedTransformations: transformations);
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
