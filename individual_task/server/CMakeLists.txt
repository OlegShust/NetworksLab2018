cmake_minimum_required(VERSION 2.8) 
project(mail_tcp_server) 

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra") 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra") 

file(GLOB SOURCE_FILES 
"main.cpp" 
"common.h" 
) 
add_executable(mail_tcp_server ${SOURCE_FILES})
target_link_libraries (mail_tcp_server -lpthread)