//© Copyright 2014-2022, Juan Linietsky, Ariel Manzur and the Godot community (CC-BY 3.0)
#ifndef CSHARP_REFCOUNTED_CLASS_H
#define CSHARP_REFCOUNTED_CLASS_H

// We don't need windows.h in this plugin but many others do and it throws up on itself all the time
// So best to include it and make sure CI warns us when we use something Microsoft took for their own goals....
#ifdef WIN32
#include <windows.h>
#endif

#include <godot_cpp/classes/ref.hpp>

#include "_csharp_global_helper.h"

using namespace godot;

class _CSharpRefCounted : public RefCounted {
    GDCLASS(_CSharpRefCounted, RefCounted);

protected:
    void *csharp_obj_handle;

public:
    _CSharpRefCounted() : RefCounted() {
        this->csharp_obj_handle = nullptr;
    }
    ~_CSharpRefCounted() {
        csharp_obj_free(this->csharp_obj_handle);
        this->csharp_obj_handle = nullptr;
    }

    void *get_csharp_obj_handle() {
        return this->csharp_obj_handle;
    }
};

#endif // CSHARP_REFCOUNTED_CLASS_H