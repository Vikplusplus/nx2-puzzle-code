
#include <iostream>
#include <fstream>

#include "Algorithms/optimalSolution.h"
#include "Algorithms/kColor/colorByColor.h"
#include "Algorithms/kColor/generateBoardState.h"
#include "Algorithms/kColor/rowByRow.h"
#include "Algorithms/numbered/generateBoardState.h"
#include "Algorithms/numbered/rowByRow.h"
#include "Algorithms/numbered/divideAndConquer.h"
#include "Algorithms/numbered/divideOnce.h"
#include "Algorithms/tests/numbered.h"
#include "Algorithms/tests/twoColor.h"
#include "Algorithms/tests/kColor.h"
#include "Algorithms/twoColor/generateBoardState.h"
#include "Algorithms/twoColor/partitionOnce.h"
#include "Algorithms/twoColor/rowByRow.h"
#include "WebAPI/API.h"

int main() {

    /*num::runTest();

    twoClr::runTest();

    kClr::runTest_kFixed();*/
    //kClr::runTest_nFixed();


    std::vector<int> boardState = num::generateSolvableBoardState(10);
    std::string moveSequence = num::divideAndConquer(boardState);

    std::cout << moveSequence << std::endl;

    for (int num : boardState) {
        std::cout << num << ",";
    }
    std::cout << std::endl;

    /*int n = 5;
    //int k = 3;
    for (int i = 0; i < 4000; i++) {

        std::vector<int> boardState = num::generateSolvableBoardState(n);
        std::vector<int> boardStateCopy = boardState;

        std::vector<int> targetState = getTargetState(boardState);

        std::string moveSequence = num::DivideAndConquer(boardState);

        if (moveSequence.find("RL") != std::string::npos) {
            std::cout << "RL detected!" << std::endl;
            for (int num : boardStateCopy) {
                std::cout << num << ",";
            }
            std::cout << std::endl;
        }
        if (boardState != targetState) {
            std::cout << "Wrong move sequence!" << std::endl;
            for (int num : boardStateCopy) {
                std::cout << num << ",";
            }
            std::cout << std::endl;
        }

        if (i % 100 == 0) {
            n++;
            //k++;
        }
    }*/

    //runAPI();
}

