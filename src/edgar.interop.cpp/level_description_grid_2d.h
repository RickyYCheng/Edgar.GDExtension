//© Copyright 2014-2022, Juan Linietsky, Ariel Manzur and the Godot community (CC-BY 3.0)
#ifndef LEVEL_DESCRIPTION_GRID_2D_CLASS_H
#define LEVEL_DESCRIPTION_GRID_2D_CLASS_H

// We don't need windows.h in this plugin but many others do and it throws up on itself all the time
// So best to include it and make sure CI warns us when we use something Microsoft took for their own goals....
#ifdef WIN32
#include <windows.h>
#endif

#include <godot_cpp/classes/ref.hpp>

#include "_csharp_global_helper.h"
#include "room_description_grid_2d.h"

using namespace godot;

extern "C" {
    void *csharp_obj_alloc_level_description_grid_2d(int minimum_room_distance = 0);
    void csharp_level_description_grid_2d_add_room(void *level_description_Ptr, void *room, int room_length, void *room_description_Ptr);
    void csharp_level_description_grid_2d_add_connection(void *level_description_Ptr, void *room_1, int room_1_length, void *room_2, int room_2_length);
}

class LevelDescriptionGrid2D : public RefCounted {
    GDCLASS(LevelDescriptionGrid2D, RefCounted)

protected:
    void *csharp_obj_handle;
    static void _bind_methods();

public:
    LevelDescriptionGrid2D() : RefCounted() {
        this->csharp_obj_handle = csharp_obj_alloc_level_description_grid_2d();
    }

    ~LevelDescriptionGrid2D() {
        if (this->csharp_obj_handle == nullptr) return;
        csharp_obj_free(this->csharp_obj_handle);
        this->csharp_obj_handle = nullptr;
    }

    void *get_csharp_obj_handle() {
        return this->csharp_obj_handle;
    }

    void add_room(String room, Ref<RoomDescriptionGrid2D> room_description);
    void add_connection(String room1, String room2);

    static Ref<LevelDescriptionGrid2D> cons(int minimum_room_distance);
};

#endif // LEVEL_DESCRIPTION_GRID_2D_CLASS_H