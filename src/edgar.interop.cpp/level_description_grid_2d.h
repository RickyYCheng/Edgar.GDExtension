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
    void *csharp_obj_alloc_level_description_grid_2d();
    void csharp_level_description_grid_2dd_add_room(void *level_description_Ptr, void *room_name_buffer, int room_name_size, void *room_description_Ptr);
    void csharp_level_description_grid_2dd_add_connection(void *level_description_Ptr, void *room_1_buffer, int room_1_size, void *room_2_buffer, int room_2_size);
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

    void add_room(String room, RoomDescriptionGrid2D *room_description);
    void add_connection(String room1, String room2);

    static LevelDescriptionGrid2D *cons();
};

#endif // LEVEL_DESCRIPTION_GRID_2D_CLASS_H