cmake_minimum_required(VERSION 3.20)

# Set project information
project(
  mystring
  VERSION 1.0
  DESCRIPTION "A simple String class"
  LANGUAGES CXX)

# Add a library target
add_library(${PROJECT_NAME})

# Define Cxx standard
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_11)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)

# Detect source files
file(GLOB_RECURSE source_files CONFIGURE_DEPENDS *.cpp *.h)
target_sources(${PROJECT_NAME} PUBLIC ${source_files})

# Add include directories
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
