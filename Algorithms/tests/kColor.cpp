
#include "kColor.h"
#include "../kColor/generateBoardState.h"
#include "../kColor/rowByRow.h"
#include "../kColor/colorByColor.h"
#include <fstream>
#include <iostream>
#include <vector>


namespace kClr {

    void runTest_kFixed() {

        std::ofstream out("TestResults/kColor_fixedK.csv");
        out << "n,RowByRow,ColorByColor\n";

        for (int n = 5; n <= 300; n++) {

            int y_RowByRow = 0;
            int y_ColorByColor = 0;

            for (int i = 0; i < 1000; i++) {
                std::vector<int> boardState = kClr::generateBoardState(n, 5);
                std::vector<int> boardStateCopy = boardState;

                std::string solution_RowByRow = kClr::rowByRow(boardState);
                boardState = boardStateCopy;

                std::string solution_ColorByColor = kClr::colorByColor(boardState);

                y_RowByRow += solution_RowByRow.size();
                y_ColorByColor += solution_ColorByColor.size();

            }

            y_RowByRow = y_RowByRow / 1000;
            y_ColorByColor = y_ColorByColor / 1000;

            out << n << "," << y_RowByRow << "," << y_ColorByColor << "\n";
            std::cout << "Testing finished for n = " << n << std::endl;
        }
        std::cout << "Test completed for k-color variation with k fixed." << std::endl;
    }

    void runTest_nFixed() {

        std::ofstream out("TestResults/kColor_fixedN.csv");
        out << "k,RowByRow,ColorByColor\n";

        for (int k = 3; k <= 297; k++) {

            int y_RowByRow = 0;
            int y_ColorByColor = 0;

            for (int i = 0; i < 500; i++) {
                std::vector<int> boardState = kClr::generateBoardState(150, k);
                std::vector<int> boardStateCopy = boardState;

                std::string solution_RowByRow = kClr::rowByRow(boardState);
                boardState = boardStateCopy;

                std::string solution_ColorByColor = kClr::colorByColor(boardState);

                y_RowByRow += solution_RowByRow.size();
                y_ColorByColor += solution_ColorByColor.size();

            }

            y_RowByRow = y_RowByRow / 500;
            y_ColorByColor = y_ColorByColor / 500;

            out << k << "," << y_RowByRow << "," << y_ColorByColor << "\n";
            std::cout << "Testing finished for k = " << k << std::endl;
        }
        std::cout << "Test completed for k-color variation with n fixed." << std::endl;
    }

}
