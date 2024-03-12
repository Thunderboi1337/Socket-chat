cmake_minimum_required(VERSION 3.10)
project(TCPCommunication)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# Add the -pedantic-errors flag to the CMAKE_C_FLAGS
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic-errors")


# Create a library called "socketlib" which includes the source file "socket.c".
# The extension is already found. Any number of sources could be listed here.
add_library(socketlib lib/socket/socket.c)

# Include directories for "socketlib".
target_include_directories(socketlib PUBLIC "${PROJECT_SOURCE_DIR}/lib/socket")

# Make an executable for the TCP server "tcp_server".
# The source file "tcp_server.c" should include the necessary headers.
add_executable(server tcp_server/tcp_server.c)

# Link the "socketlib" library with the "tcp_server" executable.
target_link_libraries(server PUBLIC socketlib)

# Make an executable for the TCP client "tcp_client".
# The source file "tcp_client.c" should include the necessary headers.
add_executable(client tcp_client/tcp_client.c)

# Link the "socketlib" library with the "tcp_client" executable.
target_link_libraries(client PUBLIC socketlib)