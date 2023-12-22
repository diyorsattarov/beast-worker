#include <thread>
#include <chrono>
#include "master.cpp"
#include "slave.cpp"

int main() {
    int port = 8080;
    std::string taskMessage = "task for Slave";
    // Initialize the master
    Master master(port, taskMessage);
    std::thread masterThread([&master]() { master.startServer(); });

    // Vector to hold slave threads
    std::vector<std::thread> slaveThreads;
    const int numberOfSlaves = 5; // Adjust the number of slaves as needed

    // Create and run slave threads
    for (int i = 0; i < numberOfSlaves; ++i) {
        slaveThreads.emplace_back([&, i]() {
            Slave slave("localhost", port, std::to_string(i)); // Create a new slave instance
            slave.connectToMaster();       // Connect each slave to the master
        });
    }

    // Join all slave threads
    for (auto& thread : slaveThreads) {
        if (thread.joinable()) {
            thread.join();
        }
    }

    // Join the master thread
    if (masterThread.joinable()) {
        masterThread.join();
    }

    return 0;
}