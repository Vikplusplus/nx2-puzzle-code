
#include "colorByColor.h"
#include "rowByRow.h"
#include "../numbered/generateBoardState.h"
#include "../optimalSolution.h"
#include "../partition.h"
#include "../solveRow.h"
#include "../numbered/rowByRow.h"

#include <cmath>

namespace kClr {

    std::string colorByColor(std::vector<int> &boardState) {

        int n = boardState.size() / 2;
        std::string moveSequence;
        int cellOfEmptySpace = getCellOfEmptySpace(boardState);

        int topRow = 0;

        std::vector<int> targetState = getTargetState(boardState);
        int k = targetState[boardState.size() - 2];

        int lowestPair = boardState.size() - 2;
        while (targetState[lowestPair] != targetState[lowestPair - 1]) lowestPair--;

        int rowOfLowestPair = floor((lowestPair - 1) / 2);

        int firstColorInRowOfLowestPair = -1;
        if (rowOfLowestPair <= n - 3) firstColorInRowOfLowestPair = targetState[2 * rowOfLowestPair];

        int currentColor;
        for (currentColor = 1; currentColor < k; currentColor++) {

            int currentColorAmount = 0;
            for (int i = 2 * topRow; i < boardState.size(); i++) {
                if (boardState[i] == currentColor) currentColorAmount++;
            }

            if (currentColorAmount == 0) {
                continue;
            }
            if (currentColor == firstColorInRowOfLowestPair) {


                int tilesExcludedFromPartition = 0;
                for (int i = 0; i < 2; i++) {
                    if (targetState[2 * rowOfLowestPair + i] == firstColorInRowOfLowestPair) tilesExcludedFromPartition++;
                }

                int j = boardState.size() - 1;
                while (tilesExcludedFromPartition) {
                    if (boardState[j] == currentColor) {
                        boardState[j] = -1;
                        tilesExcludedFromPartition--;
                        currentColorAmount--;
                    }
                    j--;
                }

                if (currentColorAmount >= 2) {

                    int bottomRow = n - 1;
                    while (!rowContainsLabel(boardState, bottomRow, currentColor)) bottomRow--;

                    if (2 * (bottomRow - topRow + 1) != currentColorAmount) {
                        if (getRowOfCell(cellOfEmptySpace) > bottomRow) {
                            moveSequence.append(moveEmptySpaceToRow(boardState, cellOfEmptySpace, bottomRow));

                            if (rowContainsLabel(boardState, bottomRow + 1, currentColor)) bottomRow++;
                        }

                        std::vector<int> boardState_partition (2 * (bottomRow - topRow + 1));
                        for (int i = 0; i < boardState_partition.size(); i++) {
                            if (2 * topRow + i != cellOfEmptySpace) {
                                boardState_partition[i] = (boardState[2 * topRow + i] == currentColor) ? 1 : 2;
                            }
                        }

                        bool secondColorExists = false;
                        for (int row = 0; row <= bottomRow - topRow; row++) {
                            if (rowContainsLabel(boardState_partition, row, 2)) {
                                secondColorExists = true;
                                break;
                            }
                        }

                        if (secondColorExists) {
                            std::string moveSequence_partition = partition_topToBottom(boardState_partition);

                            applyMoveSequence(boardState, cellOfEmptySpace, moveSequence_partition);
                            moveSequence.append(moveSequence_partition);
                        } else {
                            moveSequence.append(colFirst_moveEmptySpaceToCell(boardState, cellOfEmptySpace, 2 * bottomRow + 1));
                        }

                    }

                }


                topRow += std::floor(currentColorAmount / 2);

                std::vector<int> boardState_correctParity (2 * (n - rowOfLowestPair));

                for (int i = 2 * topRow; i < boardState.size(); i++) {
                    if (boardState[i] == -1) boardState[i] = currentColor;
                }

                int lowestPairColor = targetState[lowestPair];

                int firstCell = 2 * topRow;

                int pairColorAmount = 0;
                for (int i = 0; i < boardState_correctParity.size(); i++) {
                    if (boardState[firstCell + i] == currentColor || boardState[firstCell + i] == lowestPairColor) {
                        boardState_correctParity[i] = boardState[firstCell + i] - (currentColor - 1);

                        if (boardState[firstCell + i] == lowestPairColor) {
                            boardState_correctParity[i] += pairColorAmount;
                            pairColorAmount++;
                        }
                    }
                }

                for (int i = 0; i < boardState_correctParity.size(); i++) {
                    if (firstCell + i != cellOfEmptySpace && boardState_correctParity[i] == 0) {
                        boardState_correctParity[i] =
                            boardState[firstCell + i] - (currentColor - 1) + (pairColorAmount - 1);
                    }
                }

                std::pair cellsOfLowestPair = {
                    getCellOfTile(boardState_correctParity, pairColorAmount + (lowestPairColor != currentColor)),
                    getCellOfTile(boardState_correctParity, pairColorAmount - 1 + (lowestPairColor != currentColor))
                };

                if (!num::isBoardStateSolvable(boardState_correctParity)) {
                    std::swap(
                        boardState_correctParity[cellsOfLowestPair.first],
                        boardState_correctParity[cellsOfLowestPair.second]);
                }

                std::string moveSequence_boardStateWithCorrectParity = num::rowByRow(boardState_correctParity);

                applyMoveSequence(boardState, cellOfEmptySpace, moveSequence_boardStateWithCorrectParity);
                moveSequence.append(moveSequence_boardStateWithCorrectParity);

                return moveSequence;
            }

            if (currentColorAmount >= 2) {

                int bottomRow = n - 1;
                while (!rowContainsLabel(boardState, bottomRow, currentColor)) bottomRow--;

                if (2 * (bottomRow - topRow + 1) != currentColorAmount) {
                    if (getRowOfCell(cellOfEmptySpace) > bottomRow) {
                        moveSequence.append(moveEmptySpaceToRow(boardState, cellOfEmptySpace, bottomRow));

                        if (rowContainsLabel(boardState, bottomRow + 1, currentColor)) bottomRow++;
                    }

                    std::vector<int> boardState_partition (2 * (bottomRow - topRow + 1));
                    for (int i = 0; i < boardState_partition.size(); i++) {
                        if (2 * topRow + i != cellOfEmptySpace) {
                            boardState_partition[i] = (boardState[2 * topRow + i] == currentColor) ? 1 : 2;
                        }
                    }

                    bool secondColorExists = false;
                    for (int row = 0; row <= bottomRow - topRow; row++) {
                        if (rowContainsLabel(boardState_partition, row, 2)) {
                            secondColorExists = true;
                            break;
                        }
                    }

                    if (secondColorExists) {
                        std::string moveSequence_partition = partition_topToBottom(boardState_partition);

                        applyMoveSequence(boardState, cellOfEmptySpace, moveSequence_partition);
                        moveSequence.append(moveSequence_partition);
                    } else {
                        moveSequence.append(colFirst_moveEmptySpaceToCell(boardState, cellOfEmptySpace, 2 * bottomRow + 1));
                    }
                }
            }

            topRow += std::floor(currentColorAmount / 2);
            if (topRow > n - 3) break;

            if (currentColorAmount % 2 == 1) {
                moveSequence.append(solveRow(boardState, cellOfEmptySpace, topRow, currentColor, currentColor + 1));
                topRow++;
            }

            if (topRow > n - 3) break;
        }

        if (currentColor < k) {
            topRow = n - 2;

            std::vector<int> boardState_last2Rows (4);
            int minColor = targetState[2 * topRow];

            for (int i = 0; i < 4; i++) {
                if (boardState[2 * topRow + i] == -1) {
                    boardState_last2Rows[i] = 1;
                    boardState[2 * topRow + i] = minColor;
                }
                else if (boardState[2 * topRow + i] != 0) {
                    boardState_last2Rows[i] = boardState[2 * topRow + i] - (minColor - 1);
                }
            }

            std::string optimalSequence_last2Rows = optimalSolution(boardState_last2Rows);

            applyMoveSequence(boardState, cellOfEmptySpace, optimalSequence_last2Rows);
            moveSequence.append(optimalSequence_last2Rows);

            return moveSequence;
        }

        moveSequence.append(colFirst_moveEmptySpaceToCell(boardState, cellOfEmptySpace, 2 * n - 1));
        return moveSequence;
    }

}
