//© Copyright 2014-2022, Juan Linietsky, Ariel Manzur and the Godot community (CC-BY 3.0)
#ifndef DOOR_GRID_2D_CLASS_H
#define DOOR_GRID_2D_CLASS_H

// We don't need windows.h in this plugin but many others do and it throws up on itself all the time
// So best to include it and make sure CI warns us when we use something Microsoft took for their own goals....
#ifdef WIN32
#include <windows.h>
#endif

#include <godot_cpp/classes/ref.hpp>

#include "_csharp_global_helper.h"

using namespace godot;

extern "C" {
    void *csharp_obj_alloc_edgar_godot_generator(Dictionary *nodes, TypedArray<Dictionary> *edges, TypedArray<Dictionary> *layers);
    void csharp_obj_edgar_generator_generate(void* handle_Ptr);
}

class EdgarGodotGenerator : public RefCounted {
    GDCLASS(EdgarGodotGenerator, RefCounted);

protected:
    void *csharp_obj_handle;
    static void _bind_methods();

public:
    EdgarGodotGenerator() : RefCounted() {
        this->csharp_obj_handle = nullptr;
    }
    ~EdgarGodotGenerator() {
        if (this->csharp_obj_handle == nullptr) return;
        csharp_obj_free(this->csharp_obj_handle);
        this->csharp_obj_handle = nullptr;
    }

    void *get_csharp_obj_handle() {
        return this->csharp_obj_handle;
    }

    static Ref<EdgarGodotGenerator> cons(Dictionary nodes, TypedArray<Dictionary> edges, TypedArray<Dictionary> layers);

    Dictionary generate_layout();
};

#endif // DOOR_GRID_2D_CLASS_H