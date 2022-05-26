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

from collections import OrderedDict
from collections import namedtuple

import argparse
import sys
import urllib
import xml.etree.ElementTree as etree
import urllib.request

# parse_xml - Helper function to parse the XML file from a URL or local file.
def parse_xml(path):
    file = urllib.request.urlopen(path) if path.startswith("http") else open(path, 'r')
    with file:
        tree = etree.parse(file)
        return tree

# noneStr - returns string argument, or "" if argument is None.
def noneStr(s):
    if s:
        return s
    return ""

def parse_args():
    parser = argparse.ArgumentParser()

    # To pull the latest registry file from GitHub, pass:
    # -registry "https://raw.githubusercontent.com/KhronosGroup/OpenCL-Docs/main/xml/cl.xml"

    parser.add_argument('-registry', action='store',
                        default='cl.xml',
                        help='Use specified registry file instead of cl.xml')
    parser.add_argument('-o', action='store', dest='directory',
                        default='.',
                        help='Create target and related files in specified directory')

    args = parser.parse_args()
    return args

def load_spec(args):
    specpath = args.registry

    print('Parsing XML file from: ' + specpath)
    spec = parse_xml(specpath)
    return spec

def get_apisigs(spec):
    # Generate the API function signatures dictionary:
    apisigs = OrderedDict()
    ApiSignature = namedtuple('ApiSignature', 'Name RetType Params Suffix')
    ApiParam = namedtuple('ApiParam', 'Type TypeEnd Name')
    print('Generating API signatures dictionary...')
    for command in spec.findall('commands/command'):
        suffix = noneStr(command.get('suffix'))
        proto = command.find('proto')
        ret = noneStr(proto.text)
        name = ""
        params = ""
        for elem in proto:
            if elem.tag == 'name':
                name = noneStr(elem.text) + noneStr(elem.tail)
            else:
                ret = ret + noneStr(elem.text) + noneStr(elem.tail)
        ret = ret.strip()
        name = name.strip()

        plist = []
        for param in command.findall('param'):
            ptype = noneStr(param.text)
            ptypeend = ""
            pname = ""
            for elem in param:
                if elem.tag == 'name':
                    pname = noneStr(elem.text)
                    ptypeend = noneStr(elem.tail)
                else:
                    ptype = ptype + noneStr(elem.text) + noneStr(elem.tail)
            ptype = ptype.strip()
            ptypeend = ptypeend.strip()
            pname = pname.strip()
            plist.append(ApiParam(ptype, ptypeend, pname))

        # For an empty parameter list (for e.g. clUnloadCompiler), add a single
        # unnamed void parameter to make generation easier.
        if len(plist) == 0:
            plist.append(ApiParam("void", "", ""))

        apisigs[name] = ApiSignature(name, ret, plist, suffix)
    return apisigs

def get_apis(spec, apisigs):
    # Generate the core API dictionary:
    coreapis = OrderedDict()
    print('Generating core API dictionary...')
    for feature in spec.findall('feature'):
        version = noneStr(feature.get('name'))

        alist = []
        for function in feature.findall('require/command'):
            name = function.get('name')
            alist.append(apisigs[name])
        coreapis[version] = alist

    # Generate the extensions API dictionary:
    extapis = OrderedDict()
    print('Generating API extensions dictionary...')
    for feature in spec.findall('extensions/extension'):
        extension = noneStr(feature.get('name'))

        alist = []
        for function in feature.findall('require/command'):
            name = function.get('name')
            alist.append(apisigs[name])
        extapis[extension] = alist
    return (coreapis, extapis)


