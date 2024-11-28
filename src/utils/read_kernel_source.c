#include <CL/cl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




char *read_kernel_source(const char *filename)
{
    FILE *file = fopen("matrix_opencl/core/add.cl", "r");
    if (!file)
    {
        printf("Failed to open kernel file\n");
        exit(1);
    }

    // Get file size
    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    rewind(file);

    // Allocate memory for the source code (plus 1 for null terminator)
    char *source = (char *)malloc(size + 1);
    if (!source)
    {
        printf("Failed to allocate memory for kernel source\n");
        fclose(file);
        exit(1);
    }

    // Read the source code
    size_t read_size = fread(source, 1, size, file);
    fclose(file);

    // Add null terminator
    source[read_size] = '\0';

    return source;
}
