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

void LevelDescriptionGrid2D::_bind_methods() {
    // p_name must be same to the func name
    ClassDB::bind_static_method(get_class_static(), D_METHOD("cons"), &LevelDescriptionGrid2D::cons);
}