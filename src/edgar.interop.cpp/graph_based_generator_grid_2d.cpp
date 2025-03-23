#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/typed_array.hpp>

#include "graph_based_generator_grid_2d.h"

using namespace godot;

Ref<GraphBasedGeneratorGrid2D> GraphBasedGeneratorGrid2D::cons(Ref<LevelDescriptionGrid2D> level_description) {
    GraphBasedGeneratorGrid2D *self = memnew(GraphBasedGeneratorGrid2D);
    self->csharp_obj_handle = csharp_obj_alloc_graph_based_generator_grid_2d(level_description->get_csharp_obj_handle());
    return self;
}

Dictionary GraphBasedGeneratorGrid2D::generate_layout() {
    Dictionary dict;
    TypedArray<Dictionary> rooms;
    csharp_graph_based_generator_grid_2d_generate_layout(this->csharp_obj_handle, &rooms);
    dict["rooms"] = rooms;
    return dict;
}

void GraphBasedGeneratorGrid2D::_bind_methods() {
    // p_name must be same to the func name
    ClassDB::bind_static_method(get_class_static(), D_METHOD("cons", "level_description"), &GraphBasedGeneratorGrid2D::cons);
    ClassDB::bind_method(D_METHOD("generate_layout"), &GraphBasedGeneratorGrid2D::generate_layout);
}