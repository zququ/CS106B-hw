cmake_minimum_required(VERSION 3.20)

project(
  TestMyString
  VERSION 1.0
  DESCRIPTION "Test String class"
  LANGUAGES CXX)

if(NOT PROJECT_IS_TOP_LEVEL)
  message(FATAL_ERROR "本目录为顶层项目，禁止包含！")
endif()

add_subdirectory(mystring)
add_subdirectory(test)

