cmake_minimum_required(VERSION 3.13)

project(sudoku_solve)

set(CMAKE_CXX_STANDARD 17)

add_executable(main "main.cpp" "SudokuSolve.cpp")

add_executable(P1784 "P1784.cpp" "SudokuSolve.cpp")

add_executable(POJ3074 "POJ3074.cpp" "SudokuSolve.cpp")
