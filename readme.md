# Simple TCP client/server

I hope to build a distributed system using c++ and the communication between nodes will largely rely on TCP. The goal of this repo was to put together a very simple and reusuable template for setting up a TCP server and client.

The code uses winsock2 so to compile you need to link ws2_32. Compile and run the runClient.cpp and runServer.cpp scripts to test out the project.