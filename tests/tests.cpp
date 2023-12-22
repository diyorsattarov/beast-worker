#include <csignal>
#include <thread>
#include <chrono>
#include "include/master.h"
#include "include/slave.h"
std::atomic<bool> interrupted(false);

void signalHandler(int signum) {
    interrupted.store(true);
}

int main() {
    signal(SIGINT, signalHandler);
    int port = 8080;
    std::string taskMessage = "task for Slave";

    Master master(port, taskMessage);
    std::thread masterThread([&master]() { master.startServer(); });

    Slave slave("localhost", port, "1");
    std::thread slaveThread([&slave]() { slave.connectToMaster(); });

    // Wait for signal interruption (Ctrl+C)
    while (!interrupted.load()) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // After interruption, gracefully stop the master and slave
    // master.stopServer();  // You need to implement this method in the Master class
    // For the slave, you might need to implement a similar stop mechanism
    // or close the websocket connection to stop its operations

    // Join the threads
    if (slaveThread.joinable()) {
        slaveThread.join();
    }
    if (masterThread.joinable()) {
        masterThread.join();
    }

    std::cout << "Shutting down..." << std::endl;
    return 0;
}
