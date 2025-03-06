#include "door_grid_2d.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

extern "C" {
    int aotsample_add(int a, int b);
    void aotsample_greeting(void* print_ptr);
    void* alloc_custom_obj(void* print_ptr);
    void free_custom_obj(void* obj);
}

void gdprint(const char* str) {
    UtilityFunctions::print(str);
}

DoorGrid2D::DoorGrid2D() {
    this->csharp_obj = alloc_custom_obj(&gdprint);
}

DoorGrid2D::~DoorGrid2D() {
    free_custom_obj(this->csharp_obj);
    this->csharp_obj = nullptr;
}

void DoorGrid2D::_bind_methods() {
}