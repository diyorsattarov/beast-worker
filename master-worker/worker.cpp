#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>

int main() {
    // Sleep to wait for worker 1 to write data
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::ifstream file("/shared/data.txt");
    std::string line;
    if(file.is_open()) {
        while(getline(file, line)) {
            std::cout << "Received: " << line << std::endl;
        }
        file.close();
    }
    return 0;
}
