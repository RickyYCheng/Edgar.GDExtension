#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "_csharp_global_helper.h"
#include "manual_door_mode_grid_2d.h"

using namespace godot;

ManualDoorModeGrid2D* ManualDoorModeGrid2D::cons(TypedArray<DoorGrid2D> doors) {
    ManualDoorModeGrid2D* self = memnew(ManualDoorModeGrid2D);
    // self->csharp_obj_handle = csharp_obj_alloc_manual_door_mode_grid_2d(&doors, &get_handle_in_array, &get_array_size);
    return self;
}

void ManualDoorModeGrid2D::_bind_methods() {
    // p_name must be same to the func name
    ClassDB::bind_static_method(get_class_static(), D_METHOD("cons", "doors"), &ManualDoorModeGrid2D::cons);
}