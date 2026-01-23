#include "icd_envvars.h"
#include "icd_library.h"
#include "cl_plugin.h"
#include <stddef.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;
  char *plugin = khrIcd_getenv("PLUGIN");

  if (!plugin) {
    fprintf(stderr, "PLUGIN is not defined\n");
    return 1;
  }

  for (int i = 0; i < 10; i++) {
    void *library = khrIcdOsLibraryLoad(plugin);
    if (!library) {
      fprintf(stderr, "could not load plugin\n");
      return 1;
    }
    plugin_init_pfn init = (plugin_init_pfn)(size_t)
      khrIcdOsLibraryGetFunctionAddress(library, PLUGIN_INIT_NAME);
    if (!init) {
      fprintf(stderr, "plugin does not contain init function: %s\n", PLUGIN_INIT_NAME);
      return 1;
    }
    int res = init();
    if (PLUGIN_SUCCESS != res) {
      fprintf(stderr, "plugin initialization failed\n");
      return 1;
    }
    khrIcdOsLibraryUnload(library);
  }

  khrIcd_free_getenv(plugin);

  return 0;
}
