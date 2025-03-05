add_executable(test_server test_server.cpp)

target_link_libraries(test_server PRIVATE
        http2_server_lib
        Boost::system
        OpenSSL::SSL
        libnghttp2::libnghttp2
        GTest::GTest
        GTest::Main
)

target_include_directories(test_server PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        ${Boost_INCLUDE_DIRS}
        ${OPENSSL_INCLUDE_DIR}
        ${libnghttp2_INCLUDE_DIRS}
)

enable_testing()

include(GoogleTest)
gtest_add_tests(test_server "" AUTO)