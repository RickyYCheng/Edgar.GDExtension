#include "register_types.h"
#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include "edgar_godot_generator.h"

using namespace godot;

void gdprint(const char *str) {
    UtilityFunctions::print(str);
}

auto array_get_size(TypedArray<Dictionary> *array) {
    return array->size();
}

void iter_layers(TypedArray<Dictionary> *layers, void *csharp_delegate) {
    auto action = (void (*) (Dictionary*)) csharp_delegate;

    auto size = layers->size();
    for (auto i = 0; i < size; i++) {
        Dictionary layer = (*layers)[i];
        action(&layer);
    }
}

void iter_layer(Dictionary *layer, void *csharp_delegate) {
    auto action = (void (*)(const char*, Dictionary*))csharp_delegate;
    
    auto keys = layer->keys();
    auto keys_size = keys.size();
    for (auto i = 0; i < keys_size; i++) {
        String name = keys[i];
        Dictionary lnk = (*layer)[name];
        action(name.utf8().get_data(), &lnk);
    }
}

void iter_lnk_boundary(Dictionary *lnk, void *csharp_delegate) {
    auto action = (void (*)(int, int))csharp_delegate;
    
    PackedVector2Array pts = (*lnk)["boundary"];
    auto pts_size = pts.size();
    for (auto i = pts_size - 1; i >= 0; i--) {
        Vector2i pt = pts[i];
        action(pt.x, pt.y);
    }
}

void iter_doors(Dictionary *lnk, void *csharp_delegate) {
    auto action = (void (*)(PackedVector2Array*))csharp_delegate;

    TypedArray<PackedVector2Array> doors = (*lnk)["doors"];
    auto doors_size = doors.size();
    for (auto i = 0; i < doors_size; i++) {
        PackedVector2Array door = doors[i];
        action(&door);
    }
}

void iter_door(PackedVector2Array *door, void *csharp_delegate) {
    auto action = (void (*)(int, int, int, int))csharp_delegate;

    auto door_size = door->size();
    Vector2i pt = (*door)[0];
    for (auto i = 1; i < door_size; i++) {
        Vector2i pt_next = (*door)[i];
        action(pt.x, pt.y, pt_next.x, pt_next.y);
        pt = pt_next;
    }
}

void iter_nodes(Dictionary *nodes, void *csharp_delegate) {
    auto action = (void(*)(const char*, int, bool))csharp_delegate;

    auto keys = nodes->keys();
    auto keys_size = keys.size();
    for (auto i = 0; i < keys_size; i++) {
        String node = keys[i];
        Dictionary dict = (*nodes)[node];
        int layer = dict["edgar_layer"];
        bool is_corridor = dict["is_corridor_room"];
        action(node.utf8().get_data(), layer, is_corridor);
    }
}

void iter_edges(TypedArray<Dictionary> *edges, void *csharp_delegate) {
    auto action = (void (*) (const char*, const char*))csharp_delegate;
    
    auto edges_size = edges->size();
    for (auto i = 0; i < edges_size; i++) {
        Dictionary connection = (*edges)[i];
        String from_node = connection["from_node"];
        String to_node = connection["to_node"];
        action(from_node.utf8().get_data(), to_node.utf8().get_data());
    }
}

void initialize_types(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }

    csharp_init_global(
        &gdprint,
        &array_get_size,
        &iter_layers,
        &iter_layer,
        &iter_lnk_boundary,
        &iter_doors,
        &iter_door,
        &iter_nodes,
        &iter_edges
    );
    ClassDB::register_class<EdgarGodotGenerator>();
}

void uninitialize_types(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }
}

extern "C" {
    // Initialization.

    GDExtensionBool GDE_EXPORT edgar_gdextension_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
        GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

        init_obj.register_initializer(initialize_types);
        init_obj.register_terminator(uninitialize_types);
        init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

        return init_obj.init();
    }
}
