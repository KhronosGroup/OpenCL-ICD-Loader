#include<stdio.h>
#include<CL/cl.h>
#include<platform/icd_test_log.h>
#include "param_struct.h"

extern int test_create_calls(void);
extern int test_platforms(void);
extern int test_cl_runtime(void);
extern int test_kernel(void);
extern int test_buffer_object(void);
extern int test_program_objects(void);
extern int test_image_objects(void);
extern int test_sampler_objects(void);
extern int test_OpenGL_share(void);
extern int test_release_calls(void);
extern int test_icd_match(void);

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    test_icd_initialize_app_log();
    test_icd_initialize_stub_log();

    test_create_calls();
    test_platforms();
    test_cl_runtime();
    test_kernel();
    test_buffer_object();
    test_program_objects();
    test_image_objects();
    test_sampler_objects();
    test_OpenGL_share();
    test_release_calls();

    test_icd_close_app_log();
    test_icd_close_stub_log();
    
    if (test_icd_match()) {
        printf("ICD Loader Test FAILED\n");
        return 1;
    } else {
        printf("ICD Loader Test PASSED\n");
        return 0;
    }
}
