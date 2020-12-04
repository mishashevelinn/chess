cmake_minimum_required(VERSION 3.17)
project(chess)

set(CMAKE_CXX_STANDARD 98)


set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
add_executable(chess main.cpp Board.cpp Board.h Square.cpp Square.h Piece.cpp Piece.h Move.cpp Move.h MoveList.cpp MoveList.h Game.cpp Game.h)