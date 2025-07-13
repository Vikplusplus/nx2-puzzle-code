cmake_minimum_required(VERSION 3.29)
project(nx2_puzzle_Code)

set(CMAKE_CXX_STANDARD 20)

add_executable(nx2_puzzle_Code main.cpp
        Algorithms/General.h
        Algorithms/General.cpp
        Algorithms/OptimalSolution.h
        Algorithms/OptimalSolution.cpp
        Algorithms/numbered/RowByRow.h
        Algorithms/numbered/RowByRow.cpp
        Algorithms/numbered/generateBoardState.h
        Algorithms/numbered/generateBoardState.cpp
        Algorithms/twoColor/RowByRow.h
        Algorithms/twoColor/generateBoardState.h
        Algorithms/numbered/DivideOnce.cpp
        Algorithms/numbered/DivideOnce.h
        Algorithms/twoColor/generateBoardState.cpp
        Algorithms/twoColor/PartitionOnce.h
        Algorithms/twoColor/PartitionOnce.cpp
        Algorithms/twoColor/RowByRow.cpp
        Algorithms/kColor/generateBoardState.h
        Algorithms/kColor/RowByRow.h
        Algorithms/kColor/ColorByColor.h
        Algorithms/kColor/generateBoardState.cpp
        Algorithms/kColor/rowByRow.cpp
        Algorithms/kColor/ColorByColor.cpp
        WebAPI/API.h
        WebAPI/API.cpp
        Algorithms/numbered/DivideAndConquer.h
        Algorithms/numbered/DivideAndConquer.cpp
        Algorithms/Partition.h
        Algorithms/Partition.cpp
        Algorithms/tests/kColor.h
        Algorithms/tests/numbered.h
        Algorithms/tests/twoColor.h
        Algorithms/tests/numbered.cpp
        Algorithms/tests/twoColor.cpp
        Algorithms/tests/kColor.cpp
        Algorithms/SolveRow.h
        Algorithms/SolveRow.cpp
)

if (WIN32)
    target_link_libraries(nx2_puzzle_Code ws2_32)
endif()

