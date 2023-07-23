cmake_minimum_required(VERSION 3.24)
project(lame__)

set(CMAKE_CXX_STANDARD 17)

add_executable(lame__ main.cpp include/MP3Encoder.h MP3Encoder.cpp include/logger.h include/lame/lame.h)


target_link_libraries (${PROJECT_NAME} mp3lame )