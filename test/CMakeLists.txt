cmake_minimum_required(VERSION 3.10)

Project(Sockets)

add_executable(factorial_client factorial_socket.cpp)
add_executable(server_socket server_socket.cpp)
IF (WIN32)
	target_link_libraries(factorial_client ws2_32)
	target_link_libraries(server_socket ws2_32)
ENDIF()