
#include "rowByRow.h"

#include <iostream>

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
        // Solve last 2 rows using optimalSolution-algorithm.
        // -> Transform last 2 rows into smaller board.
        std::vector<int> last2Rows_boardState (4);

        for (int i = 0; i < 4; i++) {
        last2Rows_boardState[i] = (boardState[2 * row + i] == 0) ? 0 : boardState[2 * row + i] - 2 * row;
        }

        std::string last2Rows_optimalSolution = optimalSolution(last2Rows_boardState);

        applyMoveSequence(boardState, cellOfEmptySpace, last2Rows_optimalSolution);

        moveSequence.append(last2Rows_optimalSolution);

        return moveSequence;
    }

}






