#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/scene_state.hpp>

#include "_csharp_global_helper.h"
#include "edgar_godot_generator.h"

using namespace godot;

Ref<EdgarGodotGenerator> EdgarGodotGenerator::cons(Dictionary nodes, TypedArray<Dictionary> edges, TypedArray<Dictionary> layers) {
    EdgarGodotGenerator *self = memnew(EdgarGodotGenerator);
    self->csharp_obj_handle = csharp_obj_alloc_edgar_godot_generator(&nodes, &edges, &layers);
    return self;
}

Ref<EdgarGodotGenerator> EdgarGodotGenerator::from_resource(Ref<Resource> level) {
    if (!resource_valid(level)) {
        UtilityFunctions::push_error("The level resource is not a valid edgar level resource!");
        return nullptr;
    }

    Dictionary nodes = level->get_meta("nodes");
    TypedArray<Dictionary> edges = level->get_meta("edges");
    TypedArray<PackedStringArray> raw_layers = level->get_meta("level");
    auto layers_size = raw_layers.size();
    TypedArray<Dictionary> layers;
    for (auto i = 0; i < layers_size; i++) {
        Dictionary result;
        PackedStringArray layer = raw_layers[i];
        auto layer_size = layer.size();
        for (auto j = 0; j < layer_size; j++) {
            String name = layer[j];
            Ref<PackedScene> tmj = ResourceLoader::get_singleton()->load(name);
            Dictionary lnk = tmj->get_state()->get_node_property_value(0, 0);
            result[name] = lnk;
        }
        layers.push_back(result);
    }
    
    return cons(nodes, edges, layers);
}

void fill_result_dict(Array *rooms, const char *name, int posX, int posY, bool is_corridor, const char *template_name) {
    Dictionary room;
    room["room"] = name;
    room["position"] = Vector2(posX, posY);
    // NOTE: hide outline
    room["is_corridor"] = is_corridor;
    room["template"] = template_name;
    rooms->push_back(room);
    // NOTE: add transformation
    // NOTE: hide description
}

Dictionary EdgarGodotGenerator::generate_layout() {
    Dictionary result;
    Array rooms;
    csharp_obj_edgar_generator_generate(csharp_obj_handle, &rooms, &fill_result_dict);
    result["rooms"] = rooms;
    return result;
}

void EdgarGodotGenerator::_bind_methods() {
    // p_name must be same to the func name
    ClassDB::bind_static_method(get_class_static(), D_METHOD("cons", "nodes", "edges", "layers"), &EdgarGodotGenerator::cons);
    ClassDB::bind_method(D_METHOD("generate_layout"), &EdgarGodotGenerator::generate_layout);
}