import os
import platform

from conan import ConanFile
from conan.tools.files import copy


class QuasarProtobufsRecipe(ConanFile):
    name = "quasar.protobufs"
    version = "0.1.0"
    description = "Protobufs pack related to QuaSAR"
    author = "whs31 <whs31@github.io>"
    topics = ("grpc", "protocol", "network")
    settings = "os", "arch", "compiler", "build_type"
    # exports = "CMakeLists.txt", "cmake/*"
    exports_sources = "*", "!build/*", "!CMakeUserPresets.json", "!.git/*", "!target/*"

    def layout(self):
        pass

    def package(self):
        copy(
            self,
            pattern="*",
            dst=os.path.join(self.package_folder, "share"),
            src=os.path.join(self.source_folder, "share"),
            keep_path=True,
        )

    def package_info(self):
        self.cpp_info.set_property("cmake_file_name", "quasar.protobufs")
        # self.cpp_info.set_property("cmake_target_name", "quasar::protobufs")
        # self.cpp_info.libs = ["quasar-protobufs"]
        self.cpp_info.resdirs = ["share"]
