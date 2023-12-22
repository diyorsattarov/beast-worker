#pragma once
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <iostream>
#include <string>

namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

class Slave {
public:
    Slave(const std::string& masterHost, unsigned short port, const std::string& slaveId);

    void connectToMaster();

    void sendIdentification();
    void receiveTask();

    void sendResponse(const std::string& message);

private:
    std::string masterHost_;
    unsigned short port_;
    std::string slaveId_;
    net::io_context ioc_;
    tcp::resolver resolver_;
    websocket::stream<tcp::socket> ws_;
};