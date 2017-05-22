cmake_minimum_required(VERSION 3.7)
project(unp)

set(CMAKE_C_STANDARD 99)

LINK_DIRECTORIES(.)

set(SOURCE_FILES main.c)
add_executable(unp ${SOURCE_FILES})
target_link_libraries(unp libunp.a)

add_executable(gettimeclient gettimeclient.c)
target_link_libraries(gettimeclient libunp.a)

add_executable(time_server time_server.c)
target_link_libraries(time_server libunp.a)
