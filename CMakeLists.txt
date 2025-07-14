cmake_minimum_required(VERSION 3.29)
project(nx2-puzzle-code)

set(CMAKE_CXX_STANDARD 20)

add_executable(nx2-puzzle-code main.cpp

        Algorithms/general.h
        Algorithms/general.cpp
        Algorithms/optimalSolution.h
        Algorithms/optimalSolution.cpp
        Algorithms/partition.h
        Algorithms/partition.cpp
        Algorithms/solveRow.h
        Algorithms/solveRow.cpp

        Algorithms/numbered/divideAndConquer.h
        Algorithms/numbered/divideAndConquer.cpp
        Algorithms/numbered/divideOnce.cpp
        Algorithms/numbered/divideOnce.h
        Algorithms/numbered/generateBoardState.h
        Algorithms/numbered/generateBoardState.cpp
        Algorithms/numbered/rowByRow.h
        Algorithms/numbered/rowByRow.cpp

        Algorithms/twoColor/generateBoardState.h
        Algorithms/twoColor/generateBoardState.cpp
        Algorithms/twoColor/rowByRow.h
        Algorithms/twoColor/rowByRow.cpp
        Algorithms/twoColor/partitionOnce.h
        Algorithms/twoColor/partitionOnce.cpp

        Algorithms/kColor/colorByColor.h
        Algorithms/kColor/colorByColor.cpp
        Algorithms/kColor/generateBoardState.h
        Algorithms/kColor/generateBoardState.cpp
        Algorithms/kColor/rowByRow.h
        Algorithms/kColor/rowByRow.cpp

        WebAPI/API.h
        WebAPI/API.cpp

        Algorithms/tests/kColor.h
        Algorithms/tests/kColor.cpp
        Algorithms/tests/numbered.h
        Algorithms/tests/numbered.cpp
        Algorithms/tests/twoColor.h
        Algorithms/tests/twoColor.cpp

)

if (WIN32)
    target_link_libraries(nx2-puzzle-code ws2_32)
endif()

