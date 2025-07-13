
#include "numbered.h"
#include "../numbered/generateBoardState.h"
#include "../numbered/rowByRow.h"
#include "../numbered/divideOnce.h"
#include "../numbered/divideAndConquer.h"
#include "../optimalSolution.h"
#include <fstream>
#include <iostream>
#include <vector>

namespace num {

    void runTest() {

        std::ofstream out("TestResults/numbered.csv");
        out << "n,RowByRow,DivideOnce,DivideAndConquer\n";

        for (int n = 3; n <= 300; n++) {

            int y_RowByRow = 0;
            int y_DivideOnce = 0;
            int y_DivideAndConquer = 0;

            for (int i = 0; i < 1000; i++) {
                std::vector<int> boardState = num::generateBoardState(n);
                std::vector<int> boardStateCopy = boardState;

                std::string moveSequence_rowByRow = num::rowByRow(boardState);
                boardState = boardStateCopy;

                std::string moveSequence_DivideOnce = num::divideOnce(boardState);
                boardState = boardStateCopy;

                std::string moveSequence_DivideAndConquer = num::divideAndConquer(boardState);

                y_RowByRow += moveSequence_rowByRow.size();
                y_DivideOnce += moveSequence_DivideOnce.size();
                y_DivideAndConquer += moveSequence_DivideAndConquer.size();

            }

            y_RowByRow = y_RowByRow / 1000;
            y_DivideOnce = y_DivideOnce / 1000;
            y_DivideAndConquer = y_DivideAndConquer / 1000;

            out << n << "," << y_RowByRow << "," << y_DivideOnce << "," << y_DivideAndConquer << "\n";
            std::cout << "Testing finished for n = " << n << std::endl;
        }
        std::cout << "Test completed for numbered algorithms." << std::endl;
    }


}