#pragma once

#include <nghttp2/nghttp2.h>
#include <boost/asio.hpp>
#include <string>
#include <iostream>

class Http2Server {
public:
    Http2Server(const std::string& address, const std::string& port);

    void run();

private:
    void start_accept();

    void handle_read(const boost::system::error_code& ec, std::size_t bytes_transferred);

    void initialize_http2_session();

    static ssize_t send_callback(nghttp2_session* session, const uint8_t* data, size_t length, int flags, void* user_data);

    boost::asio::io_context io_context;
    boost::asio::ip::tcp::acceptor acceptor;
    boost::asio::ip::tcp::socket socket;
    nghttp2_session* session = nullptr;
    std::array<char, 8192> buffer{};
};