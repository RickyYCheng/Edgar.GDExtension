#include "register_types.h"
#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include "door_grid_2d.h"
#include "manual_door_mode_grid_2d.h"

using namespace godot;

void gdprint(const char *str) {
    UtilityFunctions::print(str);
}

void *get_doorhandle_from_door_array(TypedArray<DoorGrid2D> *array_Ptr, int idx) {
    DoorGrid2D *door = Object::cast_to<DoorGrid2D>((*array_Ptr)[idx]);
    return door->get_csharp_obj_handle();
}

void initialize_types(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }

    csharp_init_global(&gdprint, &get_doorhandle_from_door_array);
    ClassDB::register_class<DoorGrid2D>();
    ClassDB::register_class<ManualDoorModeGrid2D>();
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
