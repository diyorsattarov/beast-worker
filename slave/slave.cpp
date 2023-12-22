#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <iostream>
#include <string>

namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

class Slave {
public:
    Slave(const std::string& masterHost, unsigned short port)
        : masterHost_(masterHost), port_(port), resolver_(ioc_), ws_(ioc_) {}

    void connectToMaster() {
        auto const results = resolver_.resolve(masterHost_, std::to_string(port_));
        net::connect(ws_.next_layer(), results.begin(), results.end());
        ws_.handshake(masterHost_, "/");

        receiveTask();
    }

    void receiveTask() {
        beast::flat_buffer buffer;
        ws_.read(buffer);

        std::string task = beast::buffers_to_string(buffer.data());
        std::cout << "Task received: " << task << std::endl;

        // Perform task...
        sendResponse("Task completed."); // Send response back to the master
    }
    
private:
    std::string masterHost_;
    unsigned short port_;
    net::io_context ioc_;
    tcp::resolver resolver_;
    websocket::stream<tcp::socket> ws_;

    void sendResponse(const std::string& message) {
        ws_.write(net::buffer(message));
    }
};

int main() {
    try {
        Slave slave("master", 8080);
        slave.connectToMaster();
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return 0;
}
