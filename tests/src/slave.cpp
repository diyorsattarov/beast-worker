#include "../include/slave.h"

Slave::Slave(const std::string& masterHost, unsigned short port, const std::string& slaveId)
    : masterHost_(masterHost), port_(port), slaveId_(slaveId), resolver_(ioc_), ws_(ioc_) {}

void Slave::connectToMaster() {
    auto const results = resolver_.resolve(masterHost_, std::to_string(port_));
    net::connect(ws_.next_layer(), results.begin(), results.end());
    ws_.handshake(masterHost_, "/");

    sendIdentification();
    receiveTask();
}

void Slave::sendIdentification() {
    std::string identificationMessage = "Slave ID: " + slaveId_;
    ws_.write(net::buffer(identificationMessage));
}

void Slave::receiveTask() {
    beast::flat_buffer buffer;
    ws_.read(buffer);

    std::string task = beast::buffers_to_string(buffer.data());
    std::cout << "[" << slaveId_ << "] Task received: " << task << std::endl;

    // Perform task...
    sendResponse("Task completed."); // Send response back to the master
}

void Slave::sendResponse(const std::string& message) {
    std::string responseMessage = "[" + slaveId_ + "] " + message;
    ws_.write(net::buffer(responseMessage));
}

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