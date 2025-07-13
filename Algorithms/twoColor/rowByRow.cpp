
#include "rowByRow.h"

#include <iostream>

#include "partitionOnce.h"
#include "../optimalSolution.h"
#include "../solveRow.h"

namespace twoClr {

    std::string rowByRow(std::vector<int> &boardState) {

        int n = boardState.size() / 2;

        int cellOfEmptySpace = getCellOfEmptySpace(boardState);
        std::string moveSequence;

        int amountOfBlack = 0;
        for (int i = 0; i < boardState.size(); i++) {
            if (boardState[i] == 1) amountOfBlack++;
        }

        int row;
        for (row = 0; row < n - 2; row++) {

            if (amountOfBlack < 2) {

                if (amountOfBlack == 0 || boardState[2 * row] == 1) {}

                else if (boardState[2 * row + 1] == 1) {
                    moveSequence.append(colFirst_moveEmptySpaceToCell(boardState, cellOfEmptySpace, 2 * row));
                    applyMove(boardState, cellOfEmptySpace, 'L');
                    moveSequence.append("L");
                }
                else {
                    int remainingBlack = 2 * row + 2;
                    while (remainingBlack <= boardState.size() && boardState[remainingBlack] != 1) {
                        remainingBlack++;
                    }

                    if (getColOfCell(remainingBlack) != 0) {
                        moveSequence.append(colFirst_moveEmptySpaceToCell(boardState, cellOfEmptySpace, remainingBlack - 1));
                        moveSequence.append(switchColOfEmptySpace(boardState, cellOfEmptySpace));
                        remainingBlack--;
                    }

                    if (getRowOfCell(cellOfEmptySpace) > getRowOfCell(remainingBlack)
                        && getColOfCell(cellOfEmptySpace) == 0) {
                        moveSequence.append(switchColOfEmptySpace(boardState, cellOfEmptySpace));
                    }

                    moveSequence.append(rowFirst_moveEmptySpaceToCell(boardState, cellOfEmptySpace, remainingBlack - 2));
                    applyMove(boardState, cellOfEmptySpace, 'U');
                    moveSequence.append("U");

                    moveSequence.append(liftTile(boardState, cellOfEmptySpace, row));
                }

                amountOfBlack = 0;
                break;
            }

            moveSequence.append(solveRow(boardState, cellOfEmptySpace, row, 1, 1));
            amountOfBlack -= 2;
        }

        if (amountOfBlack == 0) {
            moveSequence.append(rowFirst_moveEmptySpaceToCell(boardState, cellOfEmptySpace, 2 * n - 1));
            return moveSequence;
        }

        std::vector<int> last2Rows_boardState (4);
        for (int i = 0; i < 4; i++) {
            last2Rows_boardState[i] = boardState[2 * row + i];
        }

        std::string last2Rows_optimalSolution = optimalSolution(last2Rows_boardState);

        applyMoveSequence(boardState, cellOfEmptySpace, last2Rows_optimalSolution);

        moveSequence.append(last2Rows_optimalSolution);

        return moveSequence;
    }


}
