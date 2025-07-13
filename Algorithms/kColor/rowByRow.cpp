
#include "rowByRow.h"
#include "../numbered/rowByRow.h"
#include "../optimalSolution.h"
#include "../numbered/generateBoardState.h"
#include "../solveRow.h"

namespace kClr {

    std::string rowByRow(std::vector<int> &boardState) {

        int n = boardState.size() / 2;

        int cellOfEmptySpace = getCellOfEmptySpace(boardState);

        std::vector<int> targetState = getTargetState(boardState);
        int k = targetState[2 * n - 2];

        int lowestPair = boardState.size() - 2;
        while (targetState[lowestPair] != targetState[lowestPair - 1]) lowestPair--;
        int rowOfLowestPair = (getColOfCell(lowestPair) == 1) ? getRowOfCell(lowestPair) : getRowOfCell(lowestPair) - 1;

        std::string moveSequence;

        int row;
        for (row = 0; row < n - 2; row++) {

            if (row == rowOfLowestPair) {

                std::vector<int> boardStateWithCorrectParity (2 * (n - rowOfLowestPair));

                int minColor = k - 1;
                for (int i = 2 * row; i < boardState.size(); i++) {
                    if (boardState[i] != 0 && boardState[i] < minColor) minColor = boardState[i];
                }
                int lowestPairColor = targetState[lowestPair];

                int firstCell = 2 * row;

                int pairColorAmount = 0;
                for (int i = 0; i < boardStateWithCorrectParity.size(); i++) {
                    if (boardState[firstCell + i] == minColor || boardState[firstCell + i] == lowestPairColor) {
                        boardStateWithCorrectParity[i] = boardState[firstCell + i] - (minColor - 1);

                        if (boardState[firstCell + i] == lowestPairColor) {
                            boardStateWithCorrectParity[i] += pairColorAmount;
                            pairColorAmount++;
                        }
                    }
                }

                for (int i = 0; i < boardStateWithCorrectParity.size(); i++) {
                    if (firstCell + i != cellOfEmptySpace && boardStateWithCorrectParity[i] == 0) {
                        boardStateWithCorrectParity[i] =
                            boardState[firstCell + i] - (minColor - 1) + (pairColorAmount - 1);
                    }
                }

                std::pair cellsOfLowestPair = {
                    getCellOfTile(boardStateWithCorrectParity, pairColorAmount + (lowestPairColor != minColor)),
                    getCellOfTile(boardStateWithCorrectParity, pairColorAmount - 1 + (lowestPairColor != minColor))
                };

                // If the parity is wrong, we need to swap two tiles with the same label.
                if (!num::isBoardStateSolvable(boardStateWithCorrectParity)) {
                    std::swap(
                        boardStateWithCorrectParity[cellsOfLowestPair.first],
                        boardStateWithCorrectParity[cellsOfLowestPair.second]);
                }

                std::string moveSequence_boardStateWithCorrectParity = num::rowByRow(boardStateWithCorrectParity);

                applyMoveSequence(boardState, cellOfEmptySpace, moveSequence_boardStateWithCorrectParity);
                moveSequence.append(moveSequence_boardStateWithCorrectParity);

                return moveSequence;
            }

            if (rowContainsLabel(targetState, row, k)) {

                if (targetState[2 * row] == k || boardState[2 * row] == k - 1) {}

                else if (boardState[2 * row + 1] == k - 1) {
                    moveSequence.append(colFirst_moveEmptySpaceToCell(boardState, cellOfEmptySpace, 2 * row));
                    applyMove(boardState, cellOfEmptySpace, 'L');
                    moveSequence.append("L");
                }
                else {
                    // targetTile is the last remaining tile with color k-1
                    int targetTile = 2 * row + 2;
                    while (targetTile <= boardState.size() && boardState[targetTile] != k - 1) {
                        targetTile++;
                    }
                    if (getColOfCell(targetTile) != 0) {
                        moveSequence.append(colFirst_moveEmptySpaceToCell(boardState, cellOfEmptySpace, targetTile - 1));
                        moveSequence.append(switchColOfEmptySpace(boardState, cellOfEmptySpace));
                        targetTile--;
                    }

                    if (getRowOfCell(cellOfEmptySpace) > getRowOfCell(targetTile)
                        && getColOfCell(cellOfEmptySpace) == 0) {
                        moveSequence.append(switchColOfEmptySpace(boardState, cellOfEmptySpace));
                    }

                    moveSequence.append(rowFirst_moveEmptySpaceToCell(boardState, cellOfEmptySpace, targetTile - 2));
                    applyMove(boardState, cellOfEmptySpace, 'U');
                    moveSequence.append("U");

                    moveSequence.append(liftTile(boardState, cellOfEmptySpace, row));
                }
                row++;
                break;
            }
            moveSequence.append(solveRow(boardState, cellOfEmptySpace, row, targetState[2 * row], targetState[2 * row + 1]));

        }

        if (targetState[2 * row] == k) {
            moveSequence.append(rowFirst_moveEmptySpaceToCell(boardState, cellOfEmptySpace, 2 * n - 1));
            return moveSequence;
        }

        std::vector<int> last2Rows_boardState (4);

        int minColor = k - 1;
        for (int i = 2 * row; i < boardState.size(); i++) {
            if (boardState[i] != 0 && boardState[i] < minColor) minColor = boardState[i];
        }

        for (int i = 0; i < 4; i++) {
            last2Rows_boardState[i] = (boardState[2 * row + i] == 0) ? 0 : boardState[2 * row + i] - (minColor - 1);
        }

        std::string last2Rows_optimalSequence = optimalSolution(last2Rows_boardState);

        applyMoveSequence(boardState, cellOfEmptySpace, last2Rows_optimalSequence);
        moveSequence.append(last2Rows_optimalSequence);

        return moveSequence;
    }

}
