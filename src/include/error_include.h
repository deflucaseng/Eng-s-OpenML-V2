#ifndef ERROR_INCLUDE_H
#define ERROR_INCLUDE_H

#define CHECK_ERROR(err, error_ptr)                                           \
    if (err != CL_SUCCESS)                                                   \
    {                                                                        \
        printf("[ERROR] Failed at line %d with error: %d\n", __LINE__, err); \
        *(error_ptr) = 1;                                                    \
        return;                                                             \
    }


#endif




