#include "door_grid_2d.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

extern "C" {
    int aotsample_add(int a, int b);
    void aotsample_greeting(void* print_ptr);
}

void gdprint(const char *str) {
    UtilityFunctions::print(str);
}

DoorGrid2D::DoorGrid2D() {
    aotsample_greeting(&gdprint);
}

DoorGrid2D::~DoorGrid2D() {
}

void DoorGrid2D::_bind_methods() {
}