//© Copyright 2014-2022, Juan Linietsky, Ariel Manzur and the Godot community (CC-BY 3.0)
#ifndef MANUAL_DOOR_MODE_GRID_2D_CLASS_H
#define MANUAL_DOOR_MODE_GRID_2D_CLASS_H

// We don't need windows.h in this plugin but many others do and it throws up on itself all the time
// So best to include it and make sure CI warns us when we use something Microsoft took for their own goals....
#ifdef WIN32
#include <windows.h>
#endif

#include <godot_cpp/classes/ref.hpp>

#include "_csharp_global_helper.h"
#include "door_grid_2d.h"

using namespace godot;

extern "C" {
    void *csharp_obj_alloc_manual_door_mode_grid_2d(void *array_Ptr, int size);
}

class ManualDoorModeGrid2D : public RefCounted {
    GDCLASS(ManualDoorModeGrid2D, RefCounted);

protected:
    void *csharp_obj_handle;
    static void _bind_methods();

public:
    ManualDoorModeGrid2D() : RefCounted() {
        this->csharp_obj_handle = nullptr;
    }
    ~ManualDoorModeGrid2D() {
        if (this->csharp_obj_handle == nullptr) return;
        csharp_obj_free(this->csharp_obj_handle);
        this->csharp_obj_handle = nullptr;
    }

    void *get_csharp_obj_handle() {
        return this->csharp_obj_handle;
    }
    static Ref<ManualDoorModeGrid2D> cons(TypedArray<DoorGrid2D> doors);
};

#endif // MANUAL_DOOR_MODE_GRID_2D_CLASS_H