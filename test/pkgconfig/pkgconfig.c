#ifdef __APPLE__ //Mac OSX has a different name for the header file
#include <OpenCL/opencl.h>
#else
#include <CL/opencl.h>
#endif

#include <stdio.h>  // printf
#include <stdlib.h> // malloc
#include <stdint.h> // UINTMAX_MAX
#include <string.h> // strcmp

void checkErr(cl_int err, const char * name)
{
    if (err != CL_SUCCESS)
    {
        printf("ERROR: %s (%i)\n", name, err);
        exit( err );
    }
}

int main(void)
{
    cl_int CL_err = CL_SUCCESS;
    cl_uint numPlatforms = 0;
    cl_int stub_platform_found = CL_FALSE;

    CL_err = clGetPlatformIDs(0, NULL, &numPlatforms);
    checkErr(CL_err, "clGetPlatformIDs(numPlatforms)");

    if (numPlatforms == 0)
    {
        printf("No OpenCL platform detected.\n");
        exit( -1 );
    }
    printf("Found %u platform(s)\n\n", numPlatforms);
    fflush(NULL);

    cl_platform_id* platforms = (cl_platform_id*)malloc(numPlatforms * sizeof(cl_platform_id));
    CL_err = clGetPlatformIDs(numPlatforms, platforms, NULL);
    checkErr(CL_err, "clGetPlatformIDs(platforms)");

    for (cl_uint i = 0; i < numPlatforms; ++i)
    {
        size_t vendor_length;
        CL_err = clGetPlatformInfo(platforms[i], CL_PLATFORM_VENDOR, 0, NULL, &vendor_length);
        checkErr(CL_err, "clGetPlatformInfo(CL_PLATFORM_VENDOR, NULL, &vendor_length)");

        char* platform_name = (char*)malloc(vendor_length * sizeof(char));
        CL_err = clGetPlatformInfo(platforms[i], CL_PLATFORM_VENDOR, vendor_length, platform_name, NULL);
        checkErr(CL_err, "clGetPlatformInfo(CL_PLATFORM_VENDOR, vendor_length, platform_name)");

        printf("%s\n", platform_name);

        if (strcmp(platform_name, "stubvendorxxx") == 0)
        {
            stub_platform_found = CL_TRUE;
        }

        fflush(NULL);
        free(platform_name);
    }

    if (!stub_platform_found)
    {
        printf("Did not locate stub platform\n");
        return -1;
    }

    return 0;
}
