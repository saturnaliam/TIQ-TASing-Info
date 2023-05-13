cmake_minimum_required(VERSION 3.17)
project(TTT)
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")
file(GLOB SOURCES 
${PROJECT_SOURCE_DIR}/include/*.h 
${PROJECT_SOURCE_DIR}/tiq_tas_info.cpp)
add_executable(TTT ${SOURCES})