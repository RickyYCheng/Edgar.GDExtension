//© Copyright 2014-2022, Juan Linietsky, Ariel Manzur and the Godot community (CC-BY 3.0)
#ifndef DOORGRID2D_CLASS_H
#define DOORGRID2D_CLASS_H

// We don't need windows.h in this plugin but many others do and it throws up on itself all the time
// So best to include it and make sure CI warns us when we use something Microsoft took for their own goals....
#ifdef WIN32
#include <windows.h>
#endif

#include <godot_cpp/classes/ref.hpp>

using namespace godot;

extern "C" {
    void* csharp_obj_alloc_door_grid_2d(int x1, int y1, int x2, int y2);
}

class DoorGrid2D : public RefCounted {
    GDCLASS(DoorGrid2D, RefCounted);

private:
    void* csharp_obj_handle_Ptr;

protected:
    static void _bind_methods();

public:
    DoorGrid2D();
    ~DoorGrid2D();
};

#endif // DOORGRID2D_CLASS_H