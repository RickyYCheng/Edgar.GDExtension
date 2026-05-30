#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include <godot_cpp/classes/project_settings.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/scene_state.hpp>

#include "_csharp_global_helper.h"
#include "edgar_godot_generator.h"

using namespace godot;

Ref<EdgarGodotGenerator> EdgarGodotGenerator::cons(Dictionary nodes, TypedArray<Dictionary> edges, TypedArray<Dictionary> layers) {
    EdgarGodotGenerator *self = memnew(EdgarGodotGenerator);
    self->_nodes = nodes;
    self->_edges = edges;
    self->_layers = layers;
    return self;
}

void EdgarGodotGenerator::ensure_generator() {
    if (csharp_obj_handle != nullptr) {
        return;
    }
    csharp_obj_handle = csharp_obj_alloc_edgar_godot_generator(&_nodes, &_edges, &_layers);
}

Ref<Resource> EdgarGodotGenerator::get_proxy() {
    // WARNING: function-local statics are used because class-level statics
    // of godot-cpp types appear to be initialized before the engine is ready,
    // causing the GDExtension library to fail loading (speculative).
    static Ref<Resource> _proxy;
    static String _cached_proxy_path;
    String path = ProjectSettings::get_singleton()->get_setting("Edgar/kernel/edgar_kernel_proxy", "res://addons/edgar.godot/proxy/yati/edgar_yati_proxy.gd");
    if (_cached_proxy_path != path) {
        _cached_proxy_path = path;
        _proxy = ResourceLoader::get_singleton()->exists(path) ? ResourceLoader::get_singleton()->load(path) : Ref<Resource>();
    }
    return _proxy;
}

Dictionary EdgarGodotGenerator::get_lnk(const String &template_name, Ref<Resource> proxy) {
    if (proxy.is_null()) {
        proxy = get_proxy();
    }
    if (proxy.is_valid()) {
        return proxy->call("get_lnk", template_name);
    }

    Ref<PackedScene> _template = ResourceLoader::get_singleton()->load(template_name);
    if (_template.is_null()) {
        UtilityFunctions::push_error("[Edgar.GDExtension] Failed to load template: " + template_name);
        return Dictionary();
    }
    return _template->get_state()->get_node_property_value(0, 0);
}

Ref<EdgarGodotGenerator> EdgarGodotGenerator::from_resource(Ref<Resource> level) {
    if (!resource_valid(level)) {
        UtilityFunctions::push_error("[Edgar.GDExtension] The level resource is not a valid edgar level resource!");
        return nullptr;
    }

    try {
        Dictionary nodes = level->get_meta("nodes");
        TypedArray<Dictionary> edges = level->get_meta("edges");
        TypedArray<PackedStringArray> raw_layers = level->get_meta("layers");
        Dictionary cache;
        Ref<Resource> proxy = get_proxy();
        auto layers_size = raw_layers.size();
        TypedArray<Dictionary> layers;
        for (auto i = 0; i < layers_size; i++) {
            Dictionary result;
            PackedStringArray layer = raw_layers[i];
            auto layer_size = layer.size();
            for (auto j = 0; j < layer_size; j++) {
                String name = layer[j];

                if (cache.has(name)) {
                    result[name] = cache[name];
                    continue;
                }

                Dictionary lnk = get_lnk(name, proxy);
                if (lnk.is_empty()) {
                    continue;
                }

                cache[name] = lnk;
                result[name] = lnk;
            }
            layers.push_back(result);
        }
        
        return cons(nodes, edges, layers);
    } catch (...) {
        UtilityFunctions::push_error("[Edgar.GDExtension] Failed to create generator from resource");
        return nullptr;
    }
}

void fill_result_dict(Array *rooms, const char *name, int posX, int posY, bool is_corridor, const char *template_name, int transformation, int *outline_pts, int outline_size, int doors_count, const char **doors_from_rooms, const char **doors_to_rooms, int *doors_line_data) {
    Dictionary room;
    room["room"] = name;
    room["position"] = Vector2(posX, posY);
    room["is_corridor"] = is_corridor;
    room["template"] = template_name;
    room["transformation"] = transformation;

    outline_size /= 2;
    TypedArray<Vector2i> outline;
    outline.resize(outline_size);
    for (int i = 0; i < outline_size; i++)
        outline[i] = Vector2i(outline_pts[i * 2], outline_pts[i * 2 + 1]);
    room["outline"] = outline;

    Array doors;
    for (int i = 0; i < doors_count; i++) {
        Dictionary door;
        door["from_room"] = doors_from_rooms[i];
        door["to_room"] = doors_to_rooms[i];

        Dictionary door_line;
        door_line["from"] = Vector2(doors_line_data[i * 4], doors_line_data[i * 4 + 1]);
        door_line["to"] = Vector2(doors_line_data[i * 4 + 2], doors_line_data[i * 4 + 3]);
        door["door_line"] = door_line;

        doors.push_back(door);
    }
    room["doors"] = doors;

    rooms->push_back(room);
}

void EdgarGodotGenerator::inject_seed(int seed) {
    ensure_generator();
    if (csharp_obj_handle == nullptr) {
        UtilityFunctions::push_error("[Edgar.GDExtension] Generator is not initialized. Please provide valid nodes, edges, and layers.");
        return;
    }
    csharp_obj_edgar_generator_inject_seed(csharp_obj_handle, seed);
}

Dictionary EdgarGodotGenerator::generate_layout() {
    ensure_generator();
    if (csharp_obj_handle == nullptr) {
        UtilityFunctions::push_error("[Edgar.GDExtension] Generator is not initialized. Please provide valid nodes, edges, and layers.");
        return Dictionary();
    }
    
    Dictionary result;
    Array rooms;
    csharp_obj_edgar_generator_generate(csharp_obj_handle, &rooms, &fill_result_dict);
    result["rooms"] = rooms;
    return result;
}

Dictionary EdgarGodotGenerator::generate_layout_with_seed_injection(int seed) {
    inject_seed(seed);
    return generate_layout();
}

void EdgarGodotGenerator::_bind_methods() {
    // p_name must be same to the func name
    ClassDB::bind_static_method(get_class_static(), D_METHOD("cons", "nodes", "edges", "layers"), &EdgarGodotGenerator::cons);
    ClassDB::bind_method(D_METHOD("inject_seed", "seed"), &EdgarGodotGenerator::inject_seed);
    ClassDB::bind_method(D_METHOD("generate_layout"), &EdgarGodotGenerator::generate_layout);
    ClassDB::bind_method(D_METHOD("generate_layout_with_seed_injection", "seed"), &EdgarGodotGenerator::generate_layout_with_seed_injection);
}