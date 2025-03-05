#include "server.hpp"
#include <iostream>

Http2Server::Http2Server(const std::string& address, const std::string& port)
    : acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::make_address(address), std::stoi(port))),
      socket(io_context) {
    start_accept();
}

void Http2Server::run() {
    std::cout << "HTTP/2 server is running on " << acceptor.local_endpoint() << std::endl;
    io_context.run();
}

void Http2Server::start_accept() {
    acceptor.async_accept(socket, [this](boost::system::error_code ec) {
        if (!ec) {
            std::cout << "New connection accepted!" << std::endl;

            initialize_http2_session();

            socket.async_read_some(boost::asio::buffer(buffer),
                [this](boost::system::error_code ec, std::size_t bytes_transferred) {
                    handle_read(ec, bytes_transferred);
                });
        }
        start_accept();
    });
}

void Http2Server::handle_read(const boost::system::error_code& ec, std::size_t bytes_transferred) {
    if (!ec) {
        nghttp2_session_mem_recv(session, reinterpret_cast<const uint8_t*>(buffer.data()), bytes_transferred);

        socket.async_read_some(boost::asio::buffer(buffer),
            [this](boost::system::error_code ec, std::size_t bytes_transferred) {
                handle_read(ec, bytes_transferred);
            });
    } else {
        std::cerr << "Error: " << ec.message() << std::endl;
    }
}

void Http2Server::initialize_http2_session() {
    nghttp2_session_callbacks* callbacks;
    nghttp2_session_callbacks_new(&callbacks);

    nghttp2_session_callbacks_set_send_callback(callbacks, &Http2Server::send_callback);

    nghttp2_session_server_new(&session, callbacks, this);

    nghttp2_session_callbacks_del(callbacks);
}

ssize_t Http2Server::send_callback(nghttp2_session* session, const uint8_t* data, size_t length, int flags, void* user_data) {
    auto* server = static_cast<Http2Server*>(user_data);

    boost::system::error_code ec;
    boost::asio::write(server->socket, boost::asio::buffer(data, length), ec);

    if (ec) {
        std::cerr << "Error sending data: " << ec.message() << std::endl;
        return NGHTTP2_ERR_CALLBACK_FAILURE;
    }

    return length;
}