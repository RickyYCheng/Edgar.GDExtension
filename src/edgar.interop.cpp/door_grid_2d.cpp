#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "_csharp_global_helper.h"
#include "door_grid_2d.h"

using namespace godot;

DoorGrid2D::DoorGrid2D() {
    this->csharp_obj_handle_Ptr = csharp_obj_alloc_door_grid_2d(0, 0, 0, 0);
}

DoorGrid2D::~DoorGrid2D() {
    csharp_obj_free(this->csharp_obj_handle_Ptr);
    this->csharp_obj_handle_Ptr = nullptr;
}

void DoorGrid2D::_bind_methods() {
}