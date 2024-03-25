cmake_minimum_required(VERSION 3.10)
project(TCPCommunication)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# Add the -pedantic-errors flag to the CMAKE_C_FLAGS
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic-errors")

# Create a library called "socketlib" which includes the source file "socket.c".
# The extension is already found. Any number of sources could be listed here.
add_library(socketlib lib/socket/socket.c)
add_library(hashlib lib/hash_storage/hash_storage.c)
add_library(tcp_serverlib lib/tcp_server/tcp_server.c)
add_library(unity test/unity/unity.c)

# Include directories for "socketlib" and "hashlib".
target_include_directories(socketlib PUBLIC "${PROJECT_SOURCE_DIR}/lib/socket")
target_include_directories(hashlib PUBLIC "${PROJECT_SOURCE_DIR}/lib/hash_storage")

target_include_directories(tcp_serverlib PUBLIC "${PROJECT_SOURCE_DIR}/lib/tcp_server")


target_include_directories(unity PUBLIC "${PROJECT_SOURCE_DIR}/test/unity")

# Make an executable for the TCP server "tcp_server".
# The source file "tcp_server.c" should include the necessary headers.
add_executable(server src/server.c)

# Link the "socketlib" library with the "tcp_server" executable.
target_link_libraries(tcp_serverlib PUBLIC socketlib hashlib)
target_link_libraries(server PUBLIC tcp_serverlib socketlib hashlib)

# Make an executable for the TCP client "tcp_client".
# The source file "tcp_client.c" should include the necessary headers.
add_executable(client tcp_client/tcp_client.c)

# Link the "socketlib" library with the "tcp_client" executable.
target_link_libraries(client PUBLIC socketlib)

# Make an executable for the test program.
# The source file "test.c" should include the necessary headers.
add_executable(test test/test_hash_table/test.c)

# Link the "hashlib" library with the "test" executable.
target_link_libraries(test PUBLIC hashlib unity)






