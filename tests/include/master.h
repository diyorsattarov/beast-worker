#pragma once
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <cstdlib>
namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

class Master {
public:
    Master(unsigned short port, const std::string& taskMessage);

    void startServer();

private:
    net::io_context ioc_;
    tcp::acceptor acceptor_;
    std::string taskMessage_;

    void waitForConnection() {
        acceptor_.async_accept([this](boost::system::error_code ec, tcp::socket socket) {
            if (!ec) {
                std::make_shared<Session>(std::move(socket), taskMessage_)->start();
            }
            waitForConnection();
        });
    }

    class Session : public std::enable_shared_from_this<Session> {
    public:
        Session(tcp::socket socket, const std::string& taskMessage) : ws_(std::move(socket)), taskMessage_(taskMessage) {}

        void start() {
            ws_.async_accept([self = shared_from_this()](beast::error_code ec) {
                if (!ec) self->sendTask();
            });
        }

    private:
        websocket::stream<tcp::socket> ws_;
        std::string taskMessage_;

        void sendTask() {
            ws_.async_write(net::buffer(taskMessage_),
                [self = shared_from_this()](beast::error_code ec, std::size_t bytes_transferred) {
                    if (ec) {
                        // Handle any errors that occurred during the write operation
                        std::cerr << "Write error: " << ec.message() << std::endl;
                        return;
                    }

                    std::cout << "Task message sent (" << bytes_transferred << " bytes)." << std::endl;

                    self->waitForResponse();
                });
        }

        void waitForResponse() {
            auto buffer = std::make_shared<boost::beast::flat_buffer>();

            ws_.async_read(*buffer,
                [self = shared_from_this(), buffer](beast::error_code ec, std::size_t bytes_transferred) {
                    if (ec) {
                        std::cerr << "Read error: " << ec.message() << std::endl;
                        return;
                    }

                    std::string response = boost::beast::buffers_to_string(buffer->data());
                    std::cout << "Response received: " << response << std::endl;
                    // Additional logic after receiving the response
                });
        }
    };
};