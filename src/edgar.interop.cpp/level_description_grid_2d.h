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

using namespace godot;

extern "C" {
    void *csharp_obj_alloc_level_description_grid_2d();
}

class LevelDescriptionGrid2D : public RefCounted {
    GDCLASS(LevelDescriptionGrid2D, RefCounted)

protected:
    void *csharp_obj_handle;
    static void _bind_methods();

public:
    LevelDescriptionGrid2D() : RefCounted() {
        this->csharp_obj_handle = nullptr;
    }

    ~LevelDescriptionGrid2D() {
        csharp_obj_free(this->csharp_obj_handle);
        this->csharp_obj_handle = nullptr;
    }

    void *get_csharp_obj_handle() {
        return this->csharp_obj_handle;
    }

    static LevelDescriptionGrid2D *cons();
};

#endif // LEVEL_DESCRIPTION_GRID_2D_CLASS_H