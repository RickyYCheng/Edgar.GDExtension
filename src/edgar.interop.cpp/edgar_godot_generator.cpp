#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "_csharp_global_helper.h"
#include "edgar_godot_generator.h"

using namespace godot;

Ref<EdgarGodotGenerator> EdgarGodotGenerator::cons(Dictionary nodes, TypedArray<Dictionary> edges, TypedArray<Dictionary> layers) {
    EdgarGodotGenerator *self = memnew(EdgarGodotGenerator);
    // self->csharp_obj_handle = csharp_obj_alloc_edgar_godot_generator(from.x, from.y, to.x, to.y);
    return self;
}

void EdgarGodotGenerator::_bind_methods() {
    // p_name must be same to the func name
    ClassDB::bind_static_method(get_class_static(), D_METHOD("cons", "nodes", "edges", "layers"), &EdgarGodotGenerator::cons);
}