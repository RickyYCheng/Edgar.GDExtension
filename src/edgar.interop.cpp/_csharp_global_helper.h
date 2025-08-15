#ifndef CSHARP_GLOBAL_HELPER_H
#define CSHARP_GLOBAL_HELPER_H

extern "C" {
    void csharp_init_global(
        void *gdprint
    );
    
    void csharp_obj_free(void *csharp_obj_handle_Ptr);
    void csharp_gc_collect();
}

#endif // CSHARP_GLOBAL_HELPER