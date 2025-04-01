#include<sys/stat.h>
#include<stdlib.h>
#include<stdio.h>
#include<stdarg.h>
#include<CL/cl.h>
#include<platform/icd_test_log.h>

#if defined(_WIN32)
#include <windows.h>
#endif

#define APP_LOG_FILE  "icd_test_app_log.txt"
#define STUB_LOG_FILE "icd_test_stub_log.txt"

const char * log_getenv(const char *name, const char *dflt) {
#if defined(_WIN32)
    char *retVal = NULL;
    DWORD valSize;

    valSize = GetEnvironmentVariableA(name, NULL, 0);

    // valSize DOES include the null terminator, so for any set variable
    // will always be at least 1. If it's 0, the variable wasn't set.
    if (valSize == 0) {
        if (dflt) {
            size_t sz = strlen(dflt) + 1;
            retVal = (char *)malloc(sz);
            if (retVal)
                strcpy(retVal, dflt);
        }
        return retVal;
    }

    // Allocate the space necessary for the registry entry
    retVal = (char *)malloc(valSize);

    if (NULL != retVal) {
        GetEnvironmentVariableA(name, retVal, valSize);
    }

    return retVal;
#else
    const char *var = NULL;
    var = getenv(name);
    if (!var)
        var = dflt;
    return var;
#endif
}

void log_freeenv(const char *var) {
#if defined(_WIN32)
    if (var)
        free((void *)var);
#else
    (void)var;
#endif
}

static FILE *app_log_file;
static FILE *stub_log_file;

static const char *test_icd_get_app_log_file_name(void)
{
    return log_getenv("APP_LOG_FILE", APP_LOG_FILE);
}

static const char *test_icd_get_stub_log_file_name(void)
{
    return log_getenv("APP_STUB_FILE", STUB_LOG_FILE);
}

int test_icd_initialize_app_log(void)
{
    const char *app_log_file_name = test_icd_get_app_log_file_name();
    app_log_file = fopen(app_log_file_name, "w");
    if (!app_log_file) {
        printf("Unable to open file %s\n", app_log_file_name);
        log_freeenv(app_log_file_name);
        return -1;
    }

    log_freeenv(app_log_file_name);
    return 0;
}

void test_icd_close_app_log(void)
{
    fclose(app_log_file);
}

void test_icd_app_log(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vfprintf(app_log_file, format, args);
    va_end(args);
}

int test_icd_initialize_stub_log(void)
{
    const char *stub_log_file_name = test_icd_get_stub_log_file_name();
    stub_log_file = fopen(stub_log_file_name, "w");
    if (!stub_log_file) {
        printf("Unable to open file %s\n", stub_log_file_name);
        log_freeenv(stub_log_file_name);
        return -1;
    }

    log_freeenv(stub_log_file_name);
    return 0;
}

void test_icd_close_stub_log(void)
{
    fclose(stub_log_file);
}

void test_icd_stub_log(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vfprintf(stub_log_file, format, args);
    va_end(args);
}

static char *test_icd_get_log(const char *filename)
{
    struct stat statbuf;
    FILE *fp;
    char *source = NULL;

    fp = fopen(filename, "rb");
    log_freeenv(filename);

    if (fp) {
        size_t fsize = 0;
        stat(filename, &statbuf);
        fsize = statbuf.st_size;
        source = (char *)malloc(fsize+1); // +1 for NULL terminator
        if (source) {
            if (fsize) {
                if (fread(source, fsize, 1, fp) != 1) {
                    free(source);
                    source = NULL;
                } else {
                    source[fsize] = '\0';
                }
            } else {
                // Don't fail when fsize = 0, just return empty string
                source[fsize] = '\0';
            }
        }
        fclose(fp);
    }

    return source;
}

char *test_icd_get_app_log(void)
{
    return test_icd_get_log(test_icd_get_app_log_file_name());
}

char *test_icd_get_stub_log(void)
{
    return test_icd_get_log(test_icd_get_stub_log_file_name());
}
