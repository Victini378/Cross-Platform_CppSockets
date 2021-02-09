cmake_minimum_required(VERSION 3.10)

Project(Sockets)

add_executable(factorial_client.out factorial_socket.cpp)
add_executable(server_socket.out server_socket.cpp)

enable_testing()
add_test(NAME main COMMAND main)