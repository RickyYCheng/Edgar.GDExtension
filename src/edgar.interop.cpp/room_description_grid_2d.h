//© Copyright 2014-2022, Juan Linietsky, Ariel Manzur and the Godot community (CC-BY 3.0)
#ifndef ROOM_DESCRIPTION_GRID_2D_CLASS_H
#define ROOM_DESCRIPTION_GRID_2D_CLASS_H

// We don't need windows.h in this plugin but many others do and it throws up on itself all the time
// So best to include it and make sure CI warns us when we use something Microsoft took for their own goals....
#ifdef WIN32
#include <windows.h>
#endif

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/variant/packed_vector2_array.hpp>

#include "_csharp_global_helper.h"
#include "room_template_grid_2d.h"

using namespace godot;

extern "C" {
    void *csharp_obj_alloc_room_description_grid_2d(bool is_corridor, void *array_Ptr, int size);
}

class RoomDescriptionGrid2D : public RefCounted {
    GDCLASS(RoomDescriptionGrid2D, RefCounted);

protected:
    void *csharp_obj_handle;
    static void _bind_methods();

public:    
    RoomDescriptionGrid2D() : RefCounted() {
        this->csharp_obj_handle = nullptr;
    }
    ~RoomDescriptionGrid2D() {
        if (this->csharp_obj_handle == nullptr) return;
        csharp_obj_free(this->csharp_obj_handle);
        this->csharp_obj_handle = nullptr;
    }

    void *get_csharp_obj_handle() {
        return this->csharp_obj_handle;
    }
    static RoomDescriptionGrid2D *cons(bool is_corridor, TypedArray<RoomTemplateGrid2D> room_templates);
};

#endif // ROOM_DESCRIPTION_GRID_2D_CLASS_H