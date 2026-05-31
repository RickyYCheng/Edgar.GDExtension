//© Copyright 2014-2022, Juan Linietsky, Ariel Manzur and the Godot community (CC-BY 3.0)
#ifndef EDGAR_GODOT_H
#define EDGAR_GODOT_H

// We don't need windows.h in this plugin but many others do and it throws up on itself all the time
// So best to include it and make sure CI warns us when we use something Microsoft took for their own goals....
#ifdef WIN32
#include <windows.h>
#endif

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/resource.hpp>

using namespace godot;

class EdgarGodot : public RefCounted {
    GDCLASS(EdgarGodot, RefCounted);

protected:
    static void _bind_methods();

public:
    EdgarGodot() : RefCounted() {}
    ~EdgarGodot() {}

    static Ref<Resource> get_proxy();
};

#endif // EDGAR_GODOT_H
