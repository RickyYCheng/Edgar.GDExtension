//© Copyright 2014-2022, Juan Linietsky, Ariel Manzur and the Godot community (CC-BY 3.0)
#ifndef DOOR_GRID_2D_CLASS_H
#define DOOR_GRID_2D_CLASS_H

// We don't need windows.h in this plugin but many others do and it throws up on itself all the time
// So best to include it and make sure CI warns us when we use something Microsoft took for their own goals....
#ifdef WIN32
#include <windows.h>
#endif

#include <godot_cpp/classes/ref.hpp>
#include "_csharp_ref_counted.h"

using namespace godot;

extern "C" {
    void *csharp_obj_alloc_door_grid_2d(int x1, int y1, int x2, int y2);
}

class DoorGrid2D : public _CSharpRefCounted {
    GDCLASS(DoorGrid2D, RefCounted); // use RefCounted

protected:
    static void _bind_methods();

public:
    static DoorGrid2D *cons(Vector2i from, Vector2i to);
};

#endif // DOOR_GRID_2D_CLASS_H