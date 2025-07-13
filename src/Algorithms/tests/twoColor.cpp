
#include "twoColor.h"
#include "../twoColor/generateBoardState.h"
#include "../twoColor/rowByRow.h"
#include "../twoColor/partitionOnce.h"
#include <fstream>
#include <iostream>
#include <vector>

namespace twoClr {

    void runTest() {

        std::ofstream out("TestResults/twoColor.csv");
        out << "n,RowByRow,PartitionOnce\n";

        for (int n = 5; n <= 300; n++) {

            int y_RowByRow = 0;
            int y_PartitionOnce = 0;

            for (int i = 0; i < 1000; i++) {

                std::vector<int> boardState = twoClr::generateBoardState_binomial(n, 0.5);
                std::vector<int> boardStateCopy = boardState;

                std::string solution_RowByRow = twoClr::rowByRow(boardState);
                boardState = boardStateCopy;

                std::string solution_PartitionOnce = twoClr::partitionOnce(boardState);

                y_RowByRow += solution_RowByRow.size();
                y_PartitionOnce += solution_PartitionOnce.size();

            }

            y_RowByRow = y_RowByRow / 1000;
            y_PartitionOnce = y_PartitionOnce / 1000;

            out << n << "," << y_RowByRow << "," << y_PartitionOnce << "\n";
            std::cout << "Testing finished for n = " << n << std::endl;
        }

        std::cout << "Test completed for 2-color variation." << std::endl;
    }

}
