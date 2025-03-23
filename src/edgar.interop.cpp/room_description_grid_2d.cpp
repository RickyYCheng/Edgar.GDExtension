#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/variant/packed_vector2_array.hpp>

#include "room_description_grid_2d.h"

using namespace godot;

Ref<RoomDescriptionGrid2D> RoomDescriptionGrid2D::cons(bool is_corridor, TypedArray<RoomTemplateGrid2D> room_templates) {
    RoomDescriptionGrid2D *self = memnew(RoomDescriptionGrid2D);
    self->csharp_obj_handle = csharp_obj_alloc_room_description_grid_2d(is_corridor, &room_templates, room_templates.size());
    return self;
}

void RoomDescriptionGrid2D::_bind_methods() {
    // p_name must be same to the func name
    ClassDB::bind_static_method(get_class_static(), D_METHOD("cons", "is_corridor", "room_templates"), &RoomDescriptionGrid2D::cons);
}