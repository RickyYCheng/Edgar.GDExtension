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

void *get_doorhandle_from_door_array(TypedArray<EdgarGodotGenerator> *array_Ptr, int idx) {
    EdgarGodotGenerator *door = Object::cast_to<EdgarGodotGenerator>((*array_Ptr)[idx]);
    return door->get_csharp_obj_handle();
}

char get_byte_from_packed_byte_array(PackedByteArray *array_Ptr, int idx) {
    return (*array_Ptr)[idx];
}

void get_vector2_from_packed_vector2_array(PackedVector2Array *array_Ptr, int idx, float *_out_x, float *_out_y) {
    auto v = (*array_Ptr)[idx];
    *_out_x = v.x;
    *_out_y = v.y;
}

int get_int32_from_packed_int32_array(PackedInt32Array *array_Ptr, int idx) {
    return (*array_Ptr)[idx];
}

void add_layout_room(TypedArray<Dictionary> *rooms, const char16_t *room, bool is_corridor, int posx, int posy, int transformation, const char16_t *room_template) {
    Dictionary dict;
    dict["room"] = String(room);
    dict["is_corridor"] = is_corridor;
    dict["position"] = Vector2i(posx, posy);
    dict["transformation"] = transformation;
    dict["room_template"] = room_template;
    rooms->push_back(dict);
}

void initialize_types(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }

    csharp_init_global(
        &gdprint, 
        &get_doorhandle_from_door_array,
        &get_byte_from_packed_byte_array,
        &get_vector2_from_packed_vector2_array,
        &get_int32_from_packed_int32_array,
        &add_layout_room
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
