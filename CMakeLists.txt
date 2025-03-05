cmake_minimum_required(VERSION 3.15)
project(Http2Server)

include("${CMAKE_BINARY_DIR}/Release/generators/conan_toolchain.cmake")

find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenSSL REQUIRED)
find_package(libnghttp2 REQUIRED)
find_package(GTest REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCE_FILES "src/*.cpp")
file(GLOB HEADER_FILES "src/*.hpp")

add_library(http2_server_lib ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(http2_server_lib PRIVATE
        Boost::system
        OpenSSL::SSL
        libnghttp2::libnghttp2
)

target_include_directories(http2_server_lib PRIVATE
        ${CMAKE_SOURCE_DIR}/src
)

add_executable(http2_server src/main.cpp)
target_link_libraries(http2_server PRIVATE http2_server_lib)

enable_testing()

add_subdirectory(test)