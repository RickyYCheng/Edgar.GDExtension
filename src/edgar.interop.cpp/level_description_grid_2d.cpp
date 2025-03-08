#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "_csharp_global_helper.h"
#include "level_description_grid_2d.h"

using namespace godot;

LevelDescriptionGrid2D *LevelDescriptionGrid2D::cons() {
    LevelDescriptionGrid2D *self = memnew(LevelDescriptionGrid2D);
    self->csharp_obj_handle = csharp_obj_alloc_level_description_grid_2d();
    return self;
}

void LevelDescriptionGrid2D::add_room(String room, RoomDescriptionGrid2D *room_description) {
    PackedByteArray room_buffer = room.to_utf8_buffer();
    csharp_level_description_grid_2dd_add_room(this->csharp_obj_handle, &room_buffer, room_buffer.size(), room_description->get_csharp_obj_handle());
}

void LevelDescriptionGrid2D::add_connection(String room1, String room2) {
    PackedByteArray room1_buffer = room1.to_utf8_buffer();
    PackedByteArray room2_buffer = room2.to_utf8_buffer();
    csharp_level_description_grid_2dd_add_connection(this->csharp_obj_handle, &room1_buffer, room1_buffer.size(), &room2_buffer, room2_buffer.size());
}

void LevelDescriptionGrid2D::_bind_methods() {
    // p_name must be same to the func name
    ClassDB::bind_static_method(get_class_static(), D_METHOD("cons"), &LevelDescriptionGrid2D::cons);
    ClassDB::bind_method(D_METHOD("add_room", "room", "room_description"), &LevelDescriptionGrid2D::add_room);
    ClassDB::bind_method(D_METHOD("add_connection", "room1", "room2"), &LevelDescriptionGrid2D::add_connection);
}