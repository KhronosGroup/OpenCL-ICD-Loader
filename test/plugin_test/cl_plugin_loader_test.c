/*
 * Copyright (c) 2026 The Khronos Group Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * OpenCL is a trademark of Apple Inc. used under license by Khronos.
 */

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
