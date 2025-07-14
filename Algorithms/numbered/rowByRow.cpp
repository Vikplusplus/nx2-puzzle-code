
#include "rowByRow.h"
#include "../optimalSolution.h"
#include "../solveRow.h"

namespace num {

    std::string rowByRow(std::vector<int>& boardState) {
        int n = boardState.size() / 2;

        std::string moveSequence;

        int cellOfEmptySpace = getCellOfEmptySpace(boardState);

        int row;
        for (row = 0; row < n - 2; row++) {
            moveSequence.append(solveRow(boardState, cellOfEmptySpace, row, 2 * row + 1, 2 * row + 2));
        }

        std::vector<int> boardState_last2Rows (4);

        for (int i = 0; i < 4; i++) {
        boardState_last2Rows[i] = (boardState[2 * row + i] == 0) ? 0 : boardState[2 * row + i] - 2 * row;
        }

        std::string optimalSolution_last2Rows = optimalSolution(boardState_last2Rows);

        applyMoveSequence(boardState, cellOfEmptySpace, optimalSolution_last2Rows);

        moveSequence.append(optimalSolution_last2Rows);

        return moveSequence;
    }

}






