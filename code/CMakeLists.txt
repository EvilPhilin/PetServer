cmake_minimum_required(VERSION 3.8)

project(Server)

add_library(Server Server.cpp "Source/TCPServer.cpp" "Source/TCPSession.cpp")