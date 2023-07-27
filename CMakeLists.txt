cmake_minimum_required(VERSION 3.15)

project(DataMaker)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)
set(SRC_LIST sayHello/Hello.cpp)

include_directories(thpool/include)

add_executable(${PROJECT_NAME} ${SRC_LIST})
