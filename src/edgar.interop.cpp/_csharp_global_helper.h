#ifndef CSHARP_GLOBAL_HELPER_H
#define CSHARP_GLOBAL_HELPER_H

extern "C" {
    void csharp_init_global(
        void *gdprint, 
        void *get_doorhandle_from_door_array,
        void *get_byte_from_packed_byte_array,
        void *get_vector2_from_packed_vector2_array,
        void *get_int32_from_packed_int32_array
    );
    
    void csharp_obj_free(void *csharp_obj_handle_Ptr);
    void csharp_gc_collect();
}

#endif // CSHARP_GLOBAL_HELPER