#include "../include/master.h"

Master::Master(unsigned short port, const std::string& taskMessage) : acceptor_(ioc_, {tcp::v4(), port}), taskMessage_(taskMessage) {}

void Master::startServer() {
    waitForConnection();
    ioc_.run();
}



// int main(int argc, char* argv[]) {
//     // Check if the correct number of arguments are passed
//     if (argc != 3) {
//         std::cerr << "Usage: " << argv[0] << " <port> <task_message>\n";
//         return EXIT_FAILURE;
//     }

//     // Parse the port number
//     unsigned short port = static_cast<unsigned short>(std::atoi(argv[1]));
//     if (port == 0) {
//         std::cerr << "Invalid port number.\n";
//         return EXIT_FAILURE;
//     }

//     // Get the task message
//     std::string taskMessage(argv[2]);

//     // Start the server
//     Master master(port, taskMessage);
//     master.startServer();

//     return 0;
// }