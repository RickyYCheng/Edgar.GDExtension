#include <godot_cpp/core/class_db.hpp>

#include <godot_cpp/classes/project_settings.hpp>
#include <godot_cpp/classes/resource_loader.hpp>

#include "edgar_godot.h"

using namespace godot;

Ref<Resource> EdgarGodot::get_proxy() {
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

void EdgarGodot::_bind_methods() {
    ClassDB::bind_static_method(get_class_static(), D_METHOD("get_proxy"), &EdgarGodot::get_proxy);
}
