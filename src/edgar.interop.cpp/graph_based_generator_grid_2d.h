//© Copyright 2014-2022, Juan Linietsky, Ariel Manzur and the Godot community (CC-BY 3.0)
#ifndef GRAPH_BASED_GENERATOR_GRID_2D_CLASS_H
#define GRAPH_BASED_GENERATOR_GRID_2D_CLASS_H

// We don't need windows.h in this plugin but many others do and it throws up on itself all the time
// So best to include it and make sure CI warns us when we use something Microsoft took for their own goals....
#ifdef WIN32
#include <windows.h>
#endif

#include <godot_cpp/classes/ref.hpp>

#include "_csharp_global_helper.h"
#include "level_description_grid_2d.h"

using namespace godot;

extern "C" {
    void *csharp_obj_alloc_graph_based_generator_grid_2d(void *level_description_handle);
}

class GraphBasedGeneratorGrid2D : public RefCounted {
    GDCLASS(GraphBasedGeneratorGrid2D, RefCounted);

protected:
    void *csharp_obj_handle;
    static void _bind_methods();

public:
    GraphBasedGeneratorGrid2D() : RefCounted() {
        this->csharp_obj_handle = nullptr;
    }
    ~GraphBasedGeneratorGrid2D() {
        if (this->csharp_obj_handle == nullptr) return;
        csharp_obj_free(this->csharp_obj_handle);
        this->csharp_obj_handle = nullptr;
    }

    void *get_csharp_obj_handle() {
        return this->csharp_obj_handle;
    }
    static GraphBasedGeneratorGrid2D *cons(LevelDescriptionGrid2D *level_description);
};

#endif // GRAPH_BASED_GENERATOR_GRID_2D_CLASS_H