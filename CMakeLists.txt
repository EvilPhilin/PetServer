cmake_minimum_required (VERSION 3.8)
project ("PetServer")

set(BOOST_ROOT "C:/boost-build")
set(BOOST_INCLUDEDIR "C:/boost-build/include/boost-1_83")
set(Boost_USE_STATIC_RUNTIME ON)

find_package(Boost 1.83.0 REQUIRED COMPONENTS system)
include_directories(PRIVATE ${Boost_INCLUDE_DIRS})

add_executable(Main PetServer.cpp)

add_subdirectory(code)
target_link_libraries(Main Server)