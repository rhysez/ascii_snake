cmake_minimum_required(VERSION 3.10)

project(snake_from_scratch)
set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(
  snake_from_scratch src/main.cpp
  include/board.h
  src/board/board.cpp
  )
