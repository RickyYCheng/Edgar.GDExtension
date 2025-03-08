#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/typed_array.hpp>

#include "graph_based_generator_grid_2d.h"

using namespace godot;

GraphBasedGeneratorGrid2D *GraphBasedGeneratorGrid2D::cons(LevelDescriptionGrid2D *level_description) {
    GraphBasedGeneratorGrid2D *self = memnew(GraphBasedGeneratorGrid2D);
    self->csharp_obj_handle = csharp_obj_alloc_graph_based_generator_grid_2d(level_description->get_csharp_obj_handle());
    return self;
}

void GraphBasedGeneratorGrid2D::_bind_methods() {
    // p_name must be same to the func name
    ClassDB::bind_static_method(get_class_static(), D_METHOD("cons", "level_description"), &GraphBasedGeneratorGrid2D::cons);
}