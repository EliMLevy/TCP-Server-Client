#include <winsock2.h>
#include <iostream>

class MySocketClient {
private:
    WSADATA wsaData;
    SOCKET clientSocket;
    sockaddr_in serverAddress{};
    char buffer[1024];

public:
    MySocketClient(const char* address, int port);
    ~MySocketClient();
    std::string readLine();
    void sendMessage(std::string msg);

};