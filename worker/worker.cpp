#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

int main() {
    std::ofstream file("/shared/data.txt");
    if(file.is_open()) {
        file << "Data from worker 1\n";
        file.close();
    }
    // Sleep for demonstration purposes
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return 0;
}
