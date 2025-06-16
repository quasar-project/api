import os
import platform

from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout, CMakeDeps
from conan.tools.files import copy
from conan.tools.build import check_min_cppstd


class QuasarAPIRecipe(ConanFile):
    name = "quasar.api"
    version = "cci.20250616"
    description = "QuaSAR C/C++ API "
    author = "whs31 <whs31@github.io>"
    topics = ("quasar")
    settings = "os", "arch", "compiler", "build_type"
    exports = "CMakeLists.txt", "conanfile.py"
    exports_sources = "*", "!build/*", "!CMakeUserPresets.json", "!.git/*", "!target/*"
    options = {
        "shared": [True, False],
        "test": [True, False],
    }
    default_options = {
        "shared": False,
        "test": False,
    }

    @property
    def _min_cppstd(self):
        return "17"

    def requirements(self):
        self.requires("fmt/10.2.1", transitive_headers=True, transitive_libs=True)
        self.requires("nlohmann_json/[>=3.11.2]", transitive_headers=True, transitive_libs=True)
        if self.options.test:
            self.requires("catch2/[=3.7.1]")

    def layout(self):
        cmake_layout(self)

    def validate(self):
        if self.settings.get_safe("compiler.cppstd"):
            check_min_cppstd(self, self._min_cppstd)

    def configure(self):
        self.options["fmt/*"].shared = self.options.shared

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.cache_variables["BUILD_SHARED_LIBS"] = self.options.shared
        tc.cache_variables["QUASAR_API_TESTS"] = self.options.test
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.set_property("cmake_file_name", "quasar.api")
        self.cpp_info.set_property("cmake_target_name", "quasar::api_all")
        self.cpp_info.requires = ["fmt::fmt", "nlohmann_json::nlohmann_json"]
        if self.options.test:
            self.cpp_info.requires.append("catch2::catch2")
        self.cpp_info.components["api"].set_property("cmake_target_name", "quasar::api")
        self.cpp_info.components["api"].libs = ["quasar-api"]
        if not self.options.shared:
            self.cpp_info.components["api"].defines = ["QUASAR_API_C_STATIC_LIBRARY"]
        self.cpp_info.components["api_pp"].set_property("cmake_target_name", "quasar::api++")
        self.cpp_info.components["api_pp"].libs = ["quasar-api_pp"]
        if not self.options.shared:
            self.cpp_info.components["api_pp"].defines = ["QUASAR_API_C_STATIC_LIBRARY", "QUASAR_API_STATIC_LIBRARY"]
