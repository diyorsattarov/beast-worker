#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

class MasterWorker {
public:
    MasterWorker(int port, const std::string& taskMessage);
    void startServer();
    void sendTask();

private:
    int server_fd, new_socket;
    struct sockaddr_in address;
    int port;
    std::string taskMessage;
    int opt = 1;
    socklen_t addrlen;

    void setupSocket();
    void bindSocket();
    void listenForConnections();
    void acceptConnection();
};

MasterWorker::MasterWorker(int port, const std::string& taskMessage) 
    : port(port), taskMessage(taskMessage), addrlen(sizeof(address)) {
    setupSocket();
    bindSocket();
}

void MasterWorker::setupSocket() {
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    // Forcefully attaching socket to the port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
}

void MasterWorker::bindSocket() {
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
}

void MasterWorker::listenForConnections() {
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
}

void MasterWorker::acceptConnection() {
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
}

void MasterWorker::sendTask() {
    send(new_socket, taskMessage.c_str(), taskMessage.length(), 0);
    std::cout << "Task message sent\n";
}

void MasterWorker::startServer() {
    listenForConnections();
    acceptConnection();
    sendTask();
    close(server_fd);
}

int main() {
    MasterWorker master(8080, "Task for slave worker2\n");
    master.startServer();
    return 0;
}
