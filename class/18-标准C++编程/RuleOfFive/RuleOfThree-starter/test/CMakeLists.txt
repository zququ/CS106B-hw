cmake_minimum_required(VERSION 3.20)

# Set project information
project(
  Test
  VERSION 1.0
  DESCRIPTION "A simple String class"
  LANGUAGES CXX)

# Add an executable target
add_executable(${PROJECT_NAME} main.cpp)

# Define Cxx standard
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_11)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)

# Add library
target_link_libraries(${PROJECT_NAME} PRIVATE mystring)
