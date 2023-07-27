cmake_minimum_required(VERSION 3.15)

project(Thpool)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

include_directories(../include)

aux_source_directory(. THPOOL_SRC_LIST)

add_library(${PROJECT_NAME} ${THPOOL_SRC_LIST})