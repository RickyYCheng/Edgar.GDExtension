//© Copyright 2014-2022, Juan Linietsky, Ariel Manzur and the Godot community (CC-BY 3.0)
#ifndef EDGAR_GODOT_GENERATOR_H
#define EDGAR_GODOT_GENERATOR_H

// We don't need windows.h in this plugin but many others do and it throws up on itself all the time
// So best to include it and make sure CI warns us when we use something Microsoft took for their own goals....
#ifdef WIN32
#include <windows.h>
#endif

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/resource.hpp>

#include "_csharp_global_helper.h"

using namespace godot;

extern "C" {
    void *csharp_obj_alloc_edgar_godot_generator(Dictionary *nodes, TypedArray<Dictionary> *edges, TypedArray<Dictionary> *layers);
    void csharp_obj_edgar_generator_generate(void *handle_Ptr, void *result, void *fill_room);
    void csharp_obj_edgar_generator_inject_seed(void *handle_Ptr, int seed);
}

class EdgarGodotGenerator : public RefCounted {
    GDCLASS(EdgarGodotGenerator, RefCounted);

protected:
    void *csharp_obj_handle;
    Dictionary _nodes;
    TypedArray<Dictionary> _edges;
    TypedArray<Dictionary> _layers;

    static void _bind_methods();
    void ensure_generator();

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

    static Ref<EdgarGodotGenerator> from_resource(Ref<Resource> resource);

    static bool resource_valid(Ref<Resource> resource) {
        return !resource.is_null() && resource->has_meta("is_edgar_graph");
    }

    void inject_seed(int seed);
    Dictionary generate_layout();
    Dictionary generate_layout_with_seed_injection(int seed);
};

#endif // EDGAR_GODOT_GENERATOR_H