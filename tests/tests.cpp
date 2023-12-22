#include <thread>
#include <chrono>
#include "master.cpp"
#include "slave.cpp"

int main() {
    // Initialize master and slave with appropriate parameters
    unsigned short port = 8080;
    std::string taskMessage = "Task for slave";
    Master master(port, taskMessage);
    Slave slave("localhost", port); // Assuming the Slave connects to localhost

    // Create and start the master and slave in separate threads
    std::thread masterThread([&master](){
        master.startServer();
    });

    // Give the master server some time to start up
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::thread slaveThread([&slave](){
        slave.connectToMaster(); // Assuming this method initiates the slave's operations
    });

    // Join threads to wait for their completion
    masterThread.join();
    slaveThread.join();

    return 0;
}
