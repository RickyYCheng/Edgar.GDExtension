#include "door_grid_2d.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

extern "C" {
    int aotsample_add(int a, int b);
}

DoorGrid2D::DoorGrid2D() {
}

DoorGrid2D::~DoorGrid2D() {
}

void DoorGrid2D::_init(Vector2i from, Vector2i to) {
    this->from = from;
    this->to = to;
}

Vector2i DoorGrid2D::get_from() const {
    return this->from;
}

Vector2i DoorGrid2D::get_to() const {
    return this->to;
}

int DoorGrid2D::aot_add(int a, int b) const {
    return aotsample_add(a, b);
}

void DoorGrid2D::_bind_methods() {
    ClassDB::bind_method(D_METHOD("_init", "from", "to"), &DoorGrid2D::_init);

    ClassDB::bind_method(D_METHOD("get_from"), &DoorGrid2D::get_from);
    ClassDB::bind_method(D_METHOD("get_to"), &DoorGrid2D::get_to);

    ClassDB::add_property("DoorGrid2D", PropertyInfo(Variant::VECTOR2I, "from"), "", "get_from");
    ClassDB::add_property("DoorGrid2D", PropertyInfo(Variant::VECTOR2I, "to"), "", "get_to");

    ClassDB::bind_method(D_METHOD("aot_add", "a", "b"), &DoorGrid2D::aot_add);
}