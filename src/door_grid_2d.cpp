#include "door_grid_2d.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

extern "C" {
    int aotsample_add(int a, int b);
    void aotsample_greeting(void* print_ptr);
    void* alloc_csharp_obj();
    void free_csharp_obj(void* obj);
    bool is_obj_freed(void* obj);
}

DoorGrid2D::DoorGrid2D() {
    this->csharp_obj = alloc_csharp_obj();
    UtilityFunctions::print("created");
}

DoorGrid2D::~DoorGrid2D() {
    free_csharp_obj(this->csharp_obj);
    if (is_obj_freed(this->csharp_obj))
        UtilityFunctions::print("freed");
    this->csharp_obj = nullptr;
}

void DoorGrid2D::_bind_methods() {
}