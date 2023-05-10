#include <winsock2.h>
#include <iostream>


class MySocketServer {

private:
    WSADATA wsaData;
    sockaddr_in serverAddress{};
    SOCKET serverSocket;
    char buffer[1024];
    int port;

public:
    MySocketServer(int _port);
    ~MySocketServer();
    void bindSocket();
    void startListening();
    SOCKET acceptConnection();
    void sendMessage(SOCKET clientSocket, std::string msg);
    std::string readLine(SOCKET clientSocket);
    void closeSocket();
};