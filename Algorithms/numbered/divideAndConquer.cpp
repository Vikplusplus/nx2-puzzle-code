
#include "divideAndConquer.h"
#include "rowByRow.h"
#include "../optimalSolution.h"
#include "../partition.h"
#include "../solveRow.h"

#include <cmath>
#include <iostream>
#include <list>

namespace num {

    std::string divideAndConquer(std::vector<int> &boardState) {

        int n = boardState.size() / 2;

        std::vector<int> targetState = getTargetState(boardState);

        int cellOfEmptySpace = getCellOfEmptySpace(boardState);

        std::list<int> partitionBorders = {0, n - 1};

        std::string moveSequence;

        int topRow = 0;
        while (partitionBorders.front() != n) {

            topRow = partitionBorders.front();

            auto iterator = partitionBorders.begin();
            std::advance(iterator, 1);
            int bottomRow = *iterator;

            int amountOfRows = bottomRow - topRow + 1;

            if (bottomRow - topRow <= 2) {

                if (bottomRow == n - 1) break;

                for (int row = topRow; row <= bottomRow; row++) {
                    moveSequence.append(solveRow(boardState, cellOfEmptySpace, row, 2 * row + 1, 2 * row + 2));
                }

                partitionBorders.pop_front();
                partitionBorders.front()++;
            }
            else {

                std::vector<int> boardState_partition (2 * amountOfRows);

                int minColor = targetState[2 * topRow];
                int largestBlackTile = (minColor - 1) + amountOfRows - (amountOfRows % 2 == 0);

                for (int i = 0; i < boardState_partition.size(); i++) {
                    if (boardState[2 * topRow + i] != 0) {
                        boardState_partition[i] = (boardState[2 * topRow + i] <= largestBlackTile) ? 1 : 2;
                    }
                }

                std::string partitionMoveSequence = partition_bottomToTop(boardState_partition);

                applyMoveSequence(boardState, cellOfEmptySpace, partitionMoveSequence);

                moveSequence.append(partitionMoveSequence);

                iterator = partitionBorders.begin();
                std::advance(iterator, 1);
                partitionBorders.insert(iterator, std::floor(largestBlackTile / 2));
            }

        }
        std::cout << partitionBorders.front() << std::endl;

        std::vector<int> boardState_lastRows (2 * (n - topRow));

        int minColor = targetState[2 * topRow];

        for (int i = 0; i < boardState_lastRows.size(); i++) {
            boardState_lastRows[i] = (boardState[2 * topRow + i] == 0) ? 0 : boardState[2 * topRow + i] - (minColor - 1);
        }

        std::string optimalSequence_lastRows = optimalSolution(boardState_lastRows);

        applyMoveSequence(boardState, cellOfEmptySpace, optimalSequence_lastRows);
        moveSequence.append(optimalSequence_lastRows);

        return moveSequence;
    }

}