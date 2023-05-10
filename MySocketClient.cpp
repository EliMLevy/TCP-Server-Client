#include "MySocketClient.h"

// #include <iostream>
// #include <winsock2.h>

// #include <ws2tcpip.h>
// #pragma comment(lib, "ws2_32.lib")

MySocketClient::MySocketClient(const char* address, int port) {
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock." << std::endl;
        throw std::runtime_error("Failed to initialize Winsock.");
    }

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Failed to create socket." << std::endl;
        WSACleanup();
        throw std::runtime_error("Failed to create socket.");

    }

    // Prepare the server address
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(address); // Server IP address
    serverAddress.sin_port = htons(port); // Server port

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr*) &serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "Failed to connect to the server." << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        throw std::runtime_error("Failed to connect to the server.");
    }
}

MySocketClient::~MySocketClient() {
    // Close the client socket
    closesocket(clientSocket);

    // Cleanup Winsock
    WSACleanup();
}

std::string MySocketClient::readLine() {

    bool endOfLineFound = false;
    // while(!endOfLineFound) {
    // }
    std::string output = "";
    while(!endOfLineFound) {
        if (recv(clientSocket, buffer, sizeof(buffer), 0) == SOCKET_ERROR) {
            std::cerr << "Failed to receive data from server." << std::endl;
            throw std::runtime_error("Failed to receive data from server");
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

}

void MySocketClient::sendMessage(std::string msg) {
    // Send data to the server
    if (send(clientSocket, msg.c_str(), msg.size(), 0) == SOCKET_ERROR) {
        std::cerr << "Failed to send data to the server." << std::endl;
    }

}

