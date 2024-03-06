cmake_minimum_required(VERSION 3.10)
project(TCPCommunication)

set(CMAKE_C_STANDARD 99)

# Server executable
add_executable(server tcp_server.c socket.c)

# Client executable
add_executable(client1 tcp_client1.c socket.c)
