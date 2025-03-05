cmake_minimum_required(VERSION 3.15)
project(Http2Server)

include("${CMAKE_BINARY_DIR}/generators/conan_toolchain.cmake")

find_package(Boost REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(libnghttp2 REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_FILES
        src/main.cpp
        src/server.cpp
)

add_executable(http2_server ${SOURCE_FILES})

target_link_libraries(http2_server
        Boost::boost
        OpenSSL::SSL
        libnghttp2::libnghttp2
)