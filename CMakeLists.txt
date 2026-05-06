cmake_minimum_required(VERSION 3.15)
project(cpp-logger)

file(GLOB LOGGER_SOURCES "cpp/*.cpp")

add_library(cpp-logger STATIC ${LOGGER_SOURCES})

target_include_directories(cpp-logger PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/h)

target_compile_features(cpp-logger PUBLIC cxx_std_17)