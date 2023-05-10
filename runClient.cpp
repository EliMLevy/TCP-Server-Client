#include "MySocketClient.cpp"
#include <thread>


void runServerListener(MySocketClient client);

int main() {



    MySocketClient client("127.0.0.1", 8888);
    std::cout << "Connected" << std::endl;

    std::thread t(runServerListener, client);


    while(true) {
        std::string msg;
        getline(std::cin, msg);
        
        if(msg == "exit") {
            break;
        }


        client.sendMessage(msg + "\n");


    }





    return 0;
}

void runServerListener(MySocketClient client) {
    while(true) {
        std::string msg = client.readLine();
        std::cout << msg << std::endl;
    }
}