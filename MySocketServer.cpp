#include "MySocketServer.h"
#include <stdexcept>

MySocketServer::MySocketServer(int _port) {
    port = _port;
    memset(buffer, 0, sizeof(buffer));


    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock." << std::endl;
        throw std::runtime_error("Failed to initialize Winsock.");
    }

    // Create a socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Failed to create socket." << std::endl;
        WSACleanup();
        throw std::runtime_error("Failed to create socket");
    }

    // Prepare the server address
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port); // Port number

};

MySocketServer::~MySocketServer() {
    closeSocket();
    WSACleanup();
}


void MySocketServer::bindSocket() {

    // Bind the socket to the specified IP address and port
    if (bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "Failed to bind." << std::endl;
        closeSocket();
        WSACleanup();
        throw std::runtime_error("Failed to bind");
        
    }
};

void MySocketServer::startListening() {
    // Listen for incoming connections
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Failed to listen." << std::endl;
        closeSocket();
        WSACleanup();
        throw std::runtime_error("Failed to listen");
    }
};

SOCKET MySocketServer::acceptConnection() {
    SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Failed to accept connection." << std::endl;
        closeSocket();
        WSACleanup();
        throw std::runtime_error("Failed to accept connection");
    }
    return clientSocket;
};

void MySocketServer::sendMessage(SOCKET clientSocket, std::string msg) {
    // Send a message to the client
    if (send(clientSocket, msg.c_str(), msg.size(), 0) == SOCKET_ERROR) {
        std::cerr << "Failed to send data to client." << std::endl;
        closesocket(clientSocket);
        throw std::runtime_error("Failed to send data to client");
    }
}

std::string MySocketServer::readLine(SOCKET clientSocket) {
    // Receive data from the client
    bool endOfLineFound = false;
    // while(!endOfLineFound) {
    // }
    std::string output = "";
    while(!endOfLineFound) {
        if (recv(clientSocket, buffer, sizeof(buffer), 0) == SOCKET_ERROR) {
            std::cerr << "Failed to receive data from client." << std::endl;
            throw std::runtime_error("Failed to receive data from client");
        } else {
            for(int i = 0; i < 1024; i++) {
                if(buffer[i] == '\n') {
                    endOfLineFound = true;
                    break;
                } else {
                    output += buffer[i];
                }
            }
        }
    }
    return output;
};

void MySocketServer::closeSocket() {
    closesocket(serverSocket);
    WSACleanup();
}
