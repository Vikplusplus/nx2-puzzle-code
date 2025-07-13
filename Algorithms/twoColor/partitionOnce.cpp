
#include "partitionOnce.h"
#include "../partition.h"
#include <iostream>


namespace twoClr {

    std::string partitionOnce(std::vector<int>& boardState) {

        int n = boardState.size() / 2;

        std::string moveSequence;

        moveSequence.append(partition_topToBottom(boardState));

        int cellOfEmptySpace = getCellOfEmptySpace(boardState);

        moveSequence.append(moveEmptySpaceToRow(boardState, cellOfEmptySpace, n - 1));

        return moveSequence;
    }

}
