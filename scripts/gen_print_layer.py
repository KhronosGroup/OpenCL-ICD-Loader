#!/usr/bin/python3

# Copyright (c) 2020 The Khronos Group Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import gen
from mako.template import Template
from mako.exceptions import RichTraceback

if __name__ == "__main__":
    args = gen.parse_args()
    spec = gen.load_spec(args)
    apisigs = gen.get_apisigs(spec)
    (coreapis, extapis) = gen.get_apis(spec, apisigs)

    try:
        # Create the layer cpp file from the API dictionary:
        test = open(args.directory + '/icd_print_layer_generated.c', 'wb')
        icd_layer_generated_template = Template(filename='icd_print_layer_generated.c.mako')
        test.write(
          icd_layer_generated_template.render_unicode(
              spec=spec,
              apisigs=apisigs,
              coreapis=coreapis,
              extapis=extapis).
          encode('utf-8', 'replace'))
    except:
        traceback = RichTraceback()
        for (filename, lineno, function, line) in traceback.traceback:
            print('%s(%s) : error in %s' % (filename, lineno, function))
            print('    ', line)
        print('%s: %s' % (str(traceback.error.__class__.__name__), traceback.error))
