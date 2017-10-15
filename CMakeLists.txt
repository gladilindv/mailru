cmake_minimum_required(VERSION 3.8)
project(mailru)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp logManager.cpp logManager.h logReader.cpp logReader.h spamFilter.cpp spamFilter.h)
add_executable(mailru ${SOURCE_FILES})