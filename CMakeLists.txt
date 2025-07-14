cmake_minimum_required(VERSION 3.5...4.0)
project(archiver C)
set(SOURCE 
src/main.c
src/archiving.c 
libs/stack/stack.c )
option(USE_STATIC "Use static library" ON)
message(STATUS "OS: ${CMAKE_SYSTEM_NAME}")
add_executable(${PROJECT_NAME} ${SOURCE})
