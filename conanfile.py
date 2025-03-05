from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout
from conan.tools.files import copy

class Http2ServerConan(ConanFile):
    name = "http2_server"
    version = "1.0"
    license = "MIT"
    author = "Ivan Romanchuk"
    url = "https://github.com/IRomanchuk/http2_server"
    description = "HTTP/2 server using nghttp2"
    topics = ("http2", "nghttp2", "server")
    settings = "os", "compiler", "build_type", "arch"

    requires = (
        "boost/1.87.0",
        "openssl/3.4.1",
        "libnghttp2/1.61.0",
    )

    generators = "CMakeToolchain", "CMakeDeps"

    def layout(self):
        self.folders.source = "."
        self.folders.build = "build"
        self.folders.generators = "build/generators"

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        self.copy("*.h", src="src", dst="include")

    def package_info(self):
        self.cpp_info.libs = ["http2_server"]