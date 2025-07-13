
#include "divideOnce.h"
#include "rowByRow.h"
#include <cmath>

#include <iostream>

#include "../partition.h"

namespace num {

    std::string divideOnce(std::vector<int> &boardState) {
        int n = boardState.size() / 2;

        std::vector<int> boardState_partition (2 * n);
        for (int i = 0; i < 2 * n; i++) {
            if (boardState[i] != 0) boardState_partition[i] = (boardState[i] > n) ? 2 : 1;
        }

        std::string moveSequence = partition_bottomToTop(boardState_partition);

        int cellOfEmptySpace = getCellOfEmptySpace(boardState);
        applyMoveSequence(boardState, cellOfEmptySpace, moveSequence);

        moveSequence.append(rowByRow(boardState));

        return moveSequence;
    }

}

