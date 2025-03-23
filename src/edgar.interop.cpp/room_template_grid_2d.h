//© Copyright 2014-2022, Juan Linietsky, Ariel Manzur and the Godot community (CC-BY 3.0)
#ifndef ROOM_TEMPLATE_GRID_2D_CLASS_H
#define ROOM_TEMPLATE_GRID_2D_CLASS_H

// We don't need windows.h in this plugin but many others do and it throws up on itself all the time
// So best to include it and make sure CI warns us when we use something Microsoft took for their own goals....
#ifdef WIN32
#include <windows.h>
#endif

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/variant/packed_vector2_array.hpp>

#include "_csharp_global_helper.h"
#include "manual_door_mode_grid_2d.h"

using namespace godot;

extern "C" {
    void *csharp_obj_alloc_room_template_grid_2d(
        void *name_buffer, 
        int name_buffer_size,
        void *outline,
        int outline_size,
        void *doors_handle,
        void *transformations,
        int transformations_size
    );
}

class RoomTemplateGrid2D : public RefCounted {
    GDCLASS(RoomTemplateGrid2D, RefCounted);

protected:
    void *csharp_obj_handle;
    static void _bind_methods();

public:
    enum TransformationGrid2D {
        IDENTITY = 0,
        ROTATE_90 = 1,
        ROTATE_180 = 2,
        ROTATE_270 = 3,
        MIRROR_X = 4,
        MIRROR_Y = 5,
        DIAGNOL_13 = 6,
        DIAGNOL_24 = 7,
    };
    
    RoomTemplateGrid2D() : RefCounted() {
        this->csharp_obj_handle = nullptr;
    }
    ~RoomTemplateGrid2D() {
        if (this->csharp_obj_handle == nullptr) return;
        csharp_obj_free(this->csharp_obj_handle);
        this->csharp_obj_handle = nullptr;
    }

    void *get_csharp_obj_handle() {
        return this->csharp_obj_handle;
    }
    static Ref<RoomTemplateGrid2D> cons(String name, PackedVector2Array outline, Ref<ManualDoorModeGrid2D> doors, PackedInt32Array transformations);
};

VARIANT_ENUM_CAST(RoomTemplateGrid2D::TransformationGrid2D);

#endif // ROOM_TEMPLATE_GRID_2D_CLASS_H