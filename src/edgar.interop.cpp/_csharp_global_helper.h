#ifndef CSHARP_GLOBAL_HELPER_H
#define CSHARP_GLOBAL_HELPER_H

extern "C" {
    void csharp_init_global(
        void *gdprint,
        void *array_get_size,
        void *iter_layers,
        void *iter_layer,
        void *iter_lnk_boundary,
        void *iter_doors,
        void *iter_door,
        void *iter_nodes,
        void *iter_edges,
        void *iter_transformations
    );
    
    void csharp_obj_free(void *csharp_obj_handle_Ptr);
    void csharp_gc_collect();
}

#endif // CSHARP_GLOBAL_HELPER