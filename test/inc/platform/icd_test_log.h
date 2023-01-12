#ifndef _ICD_TEST_LOG_H_
#define _ICD_TEST_LOG_H_

#if defined(_WIN32) || defined(__CYGWIN__)
    #define DllExport __declspec(dllexport)
#else
    #ifndef __has_attribute
        #define __has_attribute(x) 0  // Compatibility with non-clang compilers.
    #endif
    #if (defined(__GNUC__) && (__GNUC__ >= 4)) ||\
        (defined(__clang__) && __has_attribute(visibility))
        #define DllExport __attribute__((visibility("default")))
    #else
        #define DllExport
    #endif
#endif

DllExport int test_icd_initialize_app_log(void);
DllExport void test_icd_app_log(const char *format, ...);
DllExport void test_icd_close_app_log(void);
DllExport char *test_icd_get_stub_log(void);

DllExport int test_icd_initialize_stub_log(void);
DllExport void test_icd_stub_log(const char *format, ...);
DllExport void test_icd_close_stub_log(void);
DllExport char *test_icd_get_app_log(void);

#endif /* _ICD_TEST_LOG_H_ */
