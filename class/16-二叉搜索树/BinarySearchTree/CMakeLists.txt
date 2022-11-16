cmake_minimum_required(VERSION 3.5)

project(BinarySearchTree LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(cslib)

list(APPEND EXTRA_LIBS cslib)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC ${EXTRA_LIBS})

FILE(COPY ${EXTRA_LIBS}/spl.jar DESTINATION "${CMAKE_BINARY_DIR}")
