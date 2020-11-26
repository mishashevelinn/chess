cmake_minimum_required(VERSION 3.17)
project(chess)

set(CMAKE_CXX_STANDARD 98)

add_executable(chess main.cpp Board.cpp Board.h Entry.cpp Entry.h Piece.cpp Piece.h Move.cpp Move.h)