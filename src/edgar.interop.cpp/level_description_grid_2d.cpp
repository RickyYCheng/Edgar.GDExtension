#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "_csharp_global_helper.h"
#include "level_description_grid_2d.h"

using namespace godot;

Ref<LevelDescriptionGrid2D> LevelDescriptionGrid2D::cons(int minimum_room_distance = 0) {
    LevelDescriptionGrid2D *self = memnew(LevelDescriptionGrid2D);
    self->csharp_obj_handle = csharp_obj_alloc_level_description_grid_2d(minimum_room_distance);
    return self;
}

void LevelDescriptionGrid2D::add_room(String room, Ref<RoomDescriptionGrid2D> room_description) {
    csharp_level_description_grid_2d_add_room(this->csharp_obj_handle, (void *)room.ptr(), room.length(), room_description->get_csharp_obj_handle());
}

void LevelDescriptionGrid2D::add_connection(String room1, String room2) {
    csharp_level_description_grid_2d_add_connection(this->csharp_obj_handle, (void *)room1.ptr(), room1.length(), (void *)room2.ptr(), room2.length());
}

void LevelDescriptionGrid2D::_bind_methods() {
    // p_name must be same to the func name
    ClassDB::bind_static_method(get_class_static(), D_METHOD("cons", "minimum_room_distance"), &LevelDescriptionGrid2D::cons, DEFVAL(0));
    ClassDB::bind_method(D_METHOD("add_room", "room", "room_description"), &LevelDescriptionGrid2D::add_room);
    ClassDB::bind_method(D_METHOD("add_connection", "room1", "room2"), &LevelDescriptionGrid2D::add_connection);
}