#include <CL/cl.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/read_kernel_source.h"
#include "../src/include/error_include.h"
#include "../include/matrix.h"
#include "../include/kernel.h"



#define MAX_SOURCE_SIZE (0x100000)

void matrix_opp2mi1mo(kernel *kernel_data, matrix *input_1, matrix *input_2, matrix *output_1, int *error){
    cl_int err;

    cl_platform_id platform;
    cl_uint num_platforms;
    err = clGetPlatformIDs(1, &platform, &num_platforms);
    CHECK_ERROR(err, error);

    // Get device
    cl_device_id device;
    cl_uint num_devices;
    err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, &num_devices);
    CHECK_ERROR(err, error)

    cl_context context = clCreateContext(NULL, 1, &device, NULL, NULL, &err);
    CHECK_ERROR(err, error);

    cl_command_queue queue = clCreateCommandQueue(context, device, 0, &err);
    CHECK_ERROR(err, error);



    cl_mem input_array_1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                          input_1->width * input_1->height * sizeof(float), input_1->data, &err);
    cl_mem input_array_2 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                          input_2->width * input_2->height * sizeof(float), input_2->data, &err);
    cl_mem output_array = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         output_1->width * output_1->height * sizeof(float), NULL, &err);

    const char *kernel_source = readKernelSource(kernel_data->kernel_loc);

    cl_program program = clCreateProgramWithSource(context, 1, &kernel_source, NULL, &err);
    CHECK_ERROR(err, error);

    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    
    if (err != CL_SUCCESS)
    {
        // If there are build errors, get the error log
        size_t log_size;
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
        char *log = (char *)malloc(log_size);
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, log_size, log, NULL);
        printf("Build Error: %s\n", log);
        free(log);
        exit(1);
    }

    cl_kernel clkernel = clCreateKernel(program, kernel_data->kernel_func, &err);
    CHECK_ERROR(err, error);


    err = clSetKernelArg(clkernel, 0, sizeof(cl_mem), (void *)&input_array_1);
    err |= clSetKernelArg(clkernel, 1, sizeof(cl_mem), (void *)&input_array_2);
    err |= clSetKernelArg(clkernel, 2, sizeof(cl_mem), (void *)&output_array);
    err = clSetKernelArg(clkernel, 3, sizeof(int), (void *)&input_1->width); // Pass width instead of area
    CHECK_ERROR(err, error);

    size_t global_work_size[2] = {input_1->width, input_1->height};
    err = clEnqueueNDRangeKernel(queue, clkernel, 2, NULL, global_work_size, NULL,
                                 0, NULL, NULL); // Set work_dim to 2
    CHECK_ERROR(err, error);

    clFinish(queue);

    err = clEnqueueReadBuffer(queue, output_array, CL_TRUE, 0,
                              input_1->width *input_1->height * sizeof(float),
                              output_1->data, 0, NULL, NULL);



    CHECK_ERROR(err, error);

    clReleaseMemObject(input_array_1);
    clReleaseMemObject(input_array_2);
    clReleaseMemObject(output_array);
    clReleaseKernel(clkernel);
    clReleaseProgram(program);
    clReleaseCommandQueue(queue);
    clReleaseContext(context);

}