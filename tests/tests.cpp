#include <cstdlib>
#include <iostream>
#include <thread>

void run_command(const std::string &cmd) {
    std::system(cmd.c_str());
}

int main() {
    // Start master and slave in separate threads
    std::thread master_thread(run_command, "/master 8080 'Task for slave worker2'");
    std::thread slave_thread(run_command, "/slave master 8080");

    // Join threads to wait for their completion
    master_thread.join();
    slave_thread.join();

    return 0;
}
