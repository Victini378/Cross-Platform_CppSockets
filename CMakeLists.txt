cmake_minimum_required(VERSION 3.10)

Project(Sockets)

add_executable(factorial_client factorial_socket.cpp)
add_executable(server_socket server_socket.cpp)

enable_testing()
add_test(NAME factorial_client COMMAND factorial_client)
add_test(NAME server_server COMMAND server_socket)