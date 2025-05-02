cmake_minimum_required(VERSION 3.10)
project(Metro__Baku)


set(CMAKE_CXX_STANDARD 20)
option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)
add_library(MetroBakuLib MetroBaku.cpp)
target_include_directories(MetroBakuLib PUBLIC ${CMAKE_SOURCE_DIR})
add_executable(Metro__Baku main.cpp)
target_link_libraries(Metro__Baku PRIVATE MetroBakuLib)
