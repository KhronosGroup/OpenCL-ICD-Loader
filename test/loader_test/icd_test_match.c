#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef __APPLE__
#include <malloc.h>
#endif
#include <platform/icd_test_log.h>

int test_icd_match()
{
    int error = 0;
    char *app_log = NULL, *stub_log = NULL;

    app_log = test_icd_get_app_log();
    if (!app_log) {
        printf("ERROR: Could not retrieve app log\n");
        error = 1;
        goto End;
    }

    stub_log = test_icd_get_stub_log();
    if (!stub_log) {
        printf("ERROR: Could not retrieve stub log\n");
        error = 1;
        goto End;
    }

    if (strcmp(app_log, stub_log)) {
        printf("ERROR: App log and stub log differ.\n\n");
        printf("APPLOG:\n%s\n\n", app_log);
        printf("STUBLOG:\n%s\n\n", stub_log);
        error = 1;
        goto End;
    }

End:
    free(app_log);
    free(stub_log);
    return error;
}
