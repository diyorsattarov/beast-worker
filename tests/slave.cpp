#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <iostream>
#include <string>
#include <chrono>

namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

class Slave {
public:
    Slave(const std::string& masterHost, unsigned short port, const std::string& slaveId)
        : masterHost_(masterHost), port_(port), slaveId_(slaveId), resolver_(ioc_), ws_(ioc_) {}

    void connectToMaster() {
        auto const results = resolver_.resolve(masterHost_, std::to_string(port_));
        net::connect(ws_.next_layer(), results.begin(), results.end());
        ws_.handshake(masterHost_, "/");

        sendIdentification();
        startPingPong();
    }

    void sendIdentification() {
        std::string identificationMessage = "Slave ID: " + slaveId_;
        ws_.write(net::buffer(identificationMessage));
    }

    void startPingPong() {
        while (true) {
            sendPing();
            receivePong();
            std::this_thread::sleep_for(std::chrono::seconds(1)); // Adjust the interval as needed
        }
    }

    void sendPing() {
        std::string pingMessage = "[" + slaveId_ + "] Ping";
        ws_.write(net::buffer(pingMessage));
    }

    void receivePong() {
        beast::flat_buffer buffer;
        ws_.read(buffer);
        std::string pongMessage = beast::buffers_to_string(buffer.data());
        std::cout << "[" << slaveId_ << "] Received: " << pongMessage << std::endl;
    }

private:
    std::string masterHost_;
    unsigned short port_;
    std::string slaveId_;
    net::io_context ioc_;
    tcp::resolver resolver_;
    websocket::stream<tcp::socket> ws_;
};


// int main(int argc, char* argv[]) {
//     if (argc != 3) {
//         std::cerr << "Usage: " << argv[0] << " <masterHost> <port>\n";
//         return 1;
//     }
//     std::string masterHost = argv[1];
//     unsigned short port = std::stoi(argv[2]);

//     try {
//         Slave slave(masterHost, port);
//         slave.connectToMaster();
//     } catch (std::exception& e) {
//         std::cerr << "Error: " << e.what() << std::endl;
//         return EXIT_FAILURE;
//     }
//     return 0;
// }