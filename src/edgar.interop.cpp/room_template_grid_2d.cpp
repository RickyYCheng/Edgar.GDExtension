#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/variant/packed_vector2_array.hpp>

#include "room_template_grid_2d.h"

using namespace godot;

Ref<RoomTemplateGrid2D> RoomTemplateGrid2D::cons(String name, PackedVector2Array outline, Ref<ManualDoorModeGrid2D> doors, PackedInt32Array transformations) {
    RoomTemplateGrid2D *self = memnew(RoomTemplateGrid2D);
    self->csharp_obj_handle = csharp_obj_alloc_room_template_grid_2d((void*)name.ptr(), name.length(), &outline, outline.size(), doors->get_csharp_obj_handle(), &transformations, transformations.size());
    return self;
}

void RoomTemplateGrid2D::_bind_methods() {
    // p_name must be same to the func name
    ClassDB::bind_static_method(get_class_static(), D_METHOD("cons", "name", "outline","doors", "transformations"), &RoomTemplateGrid2D::cons);
    
    BIND_ENUM_CONSTANT(IDENTITY);
    BIND_ENUM_CONSTANT(ROTATE_90);
    BIND_ENUM_CONSTANT(ROTATE_180);
    BIND_ENUM_CONSTANT(ROTATE_270);
    BIND_ENUM_CONSTANT(MIRROR_X);
    BIND_ENUM_CONSTANT(MIRROR_Y);
    BIND_ENUM_CONSTANT(DIAGNOL_13);
    BIND_ENUM_CONSTANT(DIAGNOL_24);
}