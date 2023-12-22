#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <cstring>


class SlaveWorker {
public:
    SlaveWorker(const std::string& masterHost, int port);
    void connectToMaster();
    void receiveTask();

private:
    int sock;
    struct sockaddr_in serv_addr;
    std::string masterHost;
    int port;
};

SlaveWorker::SlaveWorker(const std::string& masterHost, int port)
    : masterHost(masterHost), port(port) {
    sock = 0;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = INADDR_ANY;
}

void SlaveWorker::connectToMaster() {
    // Creating socket file descriptor
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cout << "\nSocket creation error \n";
        exit(EXIT_FAILURE);
    }

    // Resolve the host name
    struct hostent *server;
    server = gethostbyname(masterHost.c_str());
    if (server == NULL) {
        std::cerr << "ERROR, no such host\n";
        exit(EXIT_FAILURE);
    }
    std::memcpy((char *)&serv_addr.sin_addr.s_addr, (char *)server->h_addr, server->h_length);

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cout << "\nConnection Failed \n";
        exit(EXIT_FAILURE);
    }
}

void SlaveWorker::receiveTask() {
    char buffer[1024] = {0};
    ssize_t valread = read(sock, buffer, 1024);
    std::cout << "Task received: " << buffer << std::endl;
    // Perform task...
    
    close(sock);
}

int main() {
    SlaveWorker slave("master-worker", 8080);
    slave.connectToMaster();
    slave.receiveTask();
    return 0;
}