from conans import ConanFile, CMake, tools
import os
import shutil


class KhronosopenclicdloaderConan(ConanFile):
    name = "khronos-opencl-icd-loader"
    version = "20190508"
    license = "Apache-2.0"
    author = "Khronos Group <webmaster@khronos.org"
    url = "https://github.com/KhronosGroup/opencl-icd-loader"
    description = "The OpenCL ICD Loader"
    topics = ("khronos", "opencl", "icd", "icd-loader")
    settings = "os", "compiler", "build_type", "arch"
    options = {"fPIC": [True, False], "shared": [True, False]}
    default_options = {"fPIC": True, "shared": True}
    generators = "cmake"

    exports_sources = "inc/*", "loader/*", "test/*", "CMakeLists.txt"
    
    def imports(self):
        commit = "master"
        url = "https://github.com/KhronosGroup/opencl-headers/archive/{0}.tar.gz".format(commit)
        tools.get(url)
        extracted_dir = "OpenCL-Headers-" + commit
        dest = os.path.join(self.source_folder, "inc")
        shutil.rmtree(dest)
        shutil.move(extracted_dir, dest)

    def build(self):
        cmake = CMake(self)
        cmake.definitions["USE_DYNAMIC_VCXX_RUNTIME"] = False
        cmake.configure()
        cmake.build()
        # cmake.test()
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = tools.collect_libs(self)
        if self.settings.os == "Linux":
            self.cpp_info.libs.extend(["pthread", "dl"])
        elif self.settings.os == "Windows" and \
            self.settings.get_safe("os.subsystem") != "wsl":
            self.cpp_info.libs.append("cfgmgr32")

    def configure(self):
        del self.settings.compiler.libcxx
