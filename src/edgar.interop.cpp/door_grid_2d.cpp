#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "_csharp_global_helper.h"
#include "door_grid_2d.h"

using namespace godot;

Ref<DoorGrid2D> DoorGrid2D::cons(Vector2i from, Vector2i to) {
    DoorGrid2D *self = memnew(DoorGrid2D);
    self->csharp_obj_handle = csharp_obj_alloc_door_grid_2d(from.x, from.y, to.x, to.y);
    return self;
}

void DoorGrid2D::_bind_methods() {
    // p_name must be same to the func name
    ClassDB::bind_static_method(get_class_static(), D_METHOD("cons", "from", "to"), &DoorGrid2D::cons);
}