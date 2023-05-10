#include <iostream>
#include "MySocketServer.cpp"
#include <thread>


void runClientListener(MySocketServer server, SOCKET clientSocket);

int main() {

    MySocketServer server(8888);

    server.bindSocket();
    server.startListening();
    SOCKET clientSocket = server.acceptConnection();
    std::cout << "Connected" << std::endl;

    std::thread clientListener(runClientListener, server, clientSocket);

    while(true) {
        std::string input;
        getline(std::cin, input);

        if(input == "exit") {
            break;
        }

        server.sendMessage(clientSocket, input + "\n");


    }
    
    closesocket(clientSocket);
    server.closeSocket();

    return 0;
}

void runClientListener(MySocketServer server, SOCKET clientSocket) {
    while(true) {
        std::string reply = server.readLine(clientSocket);
        std::cout << reply << std::endl; 
    }
}