from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout

class Http2ServerConan(ConanFile):
    name = "http2_server"
    version = "1.0"
    settings = "os", "compiler", "build_type", "arch"
    exports_sources = "CMakeLists.txt", "src/*"
    generators = "CMakeToolchain", "CMakeDeps"

    requires = (
        "boost/1.87.0",
        "openssl/3.2.1",
        "libnghttp2/1.61.0",
        "gtest/1.16.0",
    )

    def layout(self):
        cmake_layout(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()