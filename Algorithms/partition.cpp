
#include "partition.h"
#include <cmath>

std::string partition_topToBottom(std::vector<int>& boardState) {
    int n = boardState.size() / 2;

    int cellOfEmptySpace = getCellOfEmptySpace(boardState);

    std::string moveSequence;

    moveSequence.append(moveEmptySpaceToCol(boardState, cellOfEmptySpace, 1));

    int highestRowWithWhite = 0;
    while (!rowContainsLabel(boardState, highestRowWithWhite, 2)) highestRowWithWhite++;

    int lowerEndOfCycle = highestRowWithWhite;

    while (lowerEndOfCycle <= n - 1 && boardState[2 * lowerEndOfCycle + 1] != 1) lowerEndOfCycle++;

    bool emptySpaceAbove = getRowOfCell(cellOfEmptySpace) < lowerEndOfCycle;

    if (emptySpaceAbove) {
        moveSequence.append(moveEmptySpaceToRow(boardState, cellOfEmptySpace, highestRowWithWhite));
        if (highestRowWithWhite > 0 && rowContainsLabel(boardState, highestRowWithWhite - 1, 2)) highestRowWithWhite--;
    }
    if (!emptySpaceAbove) {
        moveSequence.append(moveEmptySpaceToRow(boardState, cellOfEmptySpace, lowerEndOfCycle));
        lowerEndOfCycle++;
    }

    while (lowerEndOfCycle <= n - 1) {

        int upperEndOfCycle = highestRowWithWhite;

        if (boardState[2 * upperEndOfCycle] == 2 && boardState[2 * upperEndOfCycle + 1] == 1){
            moveSequence.append(moveEmptySpaceToRow(boardState, cellOfEmptySpace, upperEndOfCycle));

            while (lowerEndOfCycle <= n - 1 && boardState[2 * lowerEndOfCycle + 1] != 1) {
                lowerEndOfCycle++;
            }
            continue;
        }

        while (upperEndOfCycle < lowerEndOfCycle - 1) {
            if (rowContainsLabel(boardState, upperEndOfCycle + 1, 1)) break;
            upperEndOfCycle++;
        }

        moveSequence.append(moveEmptySpaceToRow(boardState, cellOfEmptySpace, upperEndOfCycle));
        moveSequence.append(switchColOfEmptySpace(boardState, cellOfEmptySpace));
        moveSequence.append(moveEmptySpaceToRow(boardState, cellOfEmptySpace, lowerEndOfCycle));
        moveSequence.append(switchColOfEmptySpace(boardState, cellOfEmptySpace));

        if (!rowContainsLabel(boardState, highestRowWithWhite, 2)) highestRowWithWhite++;

        while (lowerEndOfCycle <= n - 1 && boardState[2 * lowerEndOfCycle + 1] != 1) {
            lowerEndOfCycle++;
        }
    }

    int lowestRowWithBlack = n - 1;
    while (boardState[2 * lowestRowWithBlack] != 1) lowestRowWithBlack--;

    int upperEndOfCycle = lowestRowWithBlack;

    while (upperEndOfCycle >= 0) {
        if (boardState[2 * upperEndOfCycle + 1] == 1) break;

        if (boardState[2 * upperEndOfCycle] == 2) {
            moveSequence.append(moveEmptySpaceToRow(boardState, cellOfEmptySpace, upperEndOfCycle));

            moveSequence.append(switchColOfEmptySpace(boardState, cellOfEmptySpace));
            moveSequence.append(moveEmptySpaceToRow(boardState, cellOfEmptySpace, lowestRowWithBlack));
            moveSequence.append(switchColOfEmptySpace(boardState, cellOfEmptySpace));
            moveSequence.append(moveEmptySpaceToRow(boardState, cellOfEmptySpace, upperEndOfCycle));

            lowestRowWithBlack--;
        }
        upperEndOfCycle--;
    }

    moveSequence.append(moveEmptySpaceToRow(boardState, cellOfEmptySpace, highestRowWithWhite));

    int phase3_iterations = ceil((lowestRowWithBlack - highestRowWithWhite) / 2.0);

    while (phase3_iterations) {

        int upperEndOfCycle = getRowOfCell(cellOfEmptySpace) + 1;

        moveSequence.append(switchColOfEmptySpace(boardState, cellOfEmptySpace));
        moveSequence.append(moveEmptySpaceToRow(boardState, cellOfEmptySpace, lowestRowWithBlack));
        moveSequence.append(switchColOfEmptySpace(boardState, cellOfEmptySpace));
        moveSequence.append(moveEmptySpaceToRow(boardState, cellOfEmptySpace, upperEndOfCycle));

        lowestRowWithBlack--;
        phase3_iterations--;
    }

    for (int i = 0; i < moveSequence.size(); i++) {
        if (moveSequence[i] == 'L' && moveSequence[i + 1] == 'R') {
            moveSequence.erase(i, 2);
        }
    }
    return moveSequence;
}

std::string partition_bottomToTop(std::vector<int>& boardState) {
    int n = boardState.size() / 2;

    int cellOfEmptySpace = getCellOfEmptySpace(boardState);

    std::string moveSequence;
    moveSequence.append(moveEmptySpaceToCol(boardState, cellOfEmptySpace, 0));

    int lowestRowWithBlack = n - 1;
    while (!rowContainsLabel(boardState, lowestRowWithBlack, 1)) {
        lowestRowWithBlack--;
    }

    int upperEndOfCycle = lowestRowWithBlack;
    while (boardState[2 * upperEndOfCycle] != 2 && upperEndOfCycle > 0) {
        upperEndOfCycle--;
    }

    bool emptySpaceBelow = getRowOfCell(cellOfEmptySpace) > upperEndOfCycle;

    if (emptySpaceBelow) {
        moveSequence.append(moveEmptySpaceToRow(boardState, cellOfEmptySpace, lowestRowWithBlack));
        if (lowestRowWithBlack < n - 1 && rowContainsLabel(boardState, lowestRowWithBlack + 1, 1)) lowestRowWithBlack++;
    }
    if (!emptySpaceBelow) {
        moveSequence.append(moveEmptySpaceToRow(boardState, cellOfEmptySpace, upperEndOfCycle));
        upperEndOfCycle--;
    }

    while (upperEndOfCycle >= 0) {

        int lowerEndOfCycle = lowestRowWithBlack;

        if (boardState[2 * lowerEndOfCycle] == 2 && boardState[2 * lowerEndOfCycle + 1] == 1) {
            moveSequence.append(moveEmptySpaceToRow(boardState, cellOfEmptySpace, lowerEndOfCycle));

            while (upperEndOfCycle >= 0 && boardState[2 * upperEndOfCycle] != 2) upperEndOfCycle--;
            continue;
        }

        while (lowerEndOfCycle > upperEndOfCycle + 1) {
            if (rowContainsLabel(boardState, lowerEndOfCycle - 1, 2)) break;
            lowerEndOfCycle--;
        }

        moveSequence.append(moveEmptySpaceToRow(boardState, cellOfEmptySpace, lowerEndOfCycle));
        moveSequence.append(switchColOfEmptySpace(boardState, cellOfEmptySpace));
        moveSequence.append(moveEmptySpaceToRow(boardState, cellOfEmptySpace, upperEndOfCycle));
        moveSequence.append(switchColOfEmptySpace(boardState, cellOfEmptySpace));

        if (!rowContainsLabel(boardState, lowestRowWithBlack, 1)) lowestRowWithBlack--;

        while (upperEndOfCycle >= 0 && boardState[2 * upperEndOfCycle] != 2) upperEndOfCycle--;
    }

    int highestRowWithWhite = 0;
    while (boardState[2 * highestRowWithWhite + 1] != 2) highestRowWithWhite++;

    int lowerEndOfCycle = highestRowWithWhite;

    while (lowerEndOfCycle <= n - 1) {
        if (boardState[2 * lowerEndOfCycle] == 2) break;

        if (boardState[2 * lowerEndOfCycle + 1] == 1) {
            moveSequence.append(moveEmptySpaceToRow(boardState, cellOfEmptySpace, lowerEndOfCycle));

            moveSequence.append(switchColOfEmptySpace(boardState, cellOfEmptySpace));
            moveSequence.append(moveEmptySpaceToRow(boardState, cellOfEmptySpace, highestRowWithWhite));
            moveSequence.append(switchColOfEmptySpace(boardState, cellOfEmptySpace));
            moveSequence.append(moveEmptySpaceToRow(boardState, cellOfEmptySpace, lowerEndOfCycle));

            highestRowWithWhite++;
        }
        lowerEndOfCycle++;
    }

    moveSequence.append(moveEmptySpaceToRow(boardState, cellOfEmptySpace, lowestRowWithBlack));

    int phase3_iterations = ceil((lowestRowWithBlack - highestRowWithWhite) / 2.0);

    while (phase3_iterations) {

        int lowerEndOfCycle = getRowOfCell(cellOfEmptySpace) - 1;

        moveSequence.append(switchColOfEmptySpace(boardState, cellOfEmptySpace));
        moveSequence.append(moveEmptySpaceToRow(boardState, cellOfEmptySpace, highestRowWithWhite));

        if (getRowOfCell(cellOfEmptySpace) != lowerEndOfCycle) {
            moveSequence.append(switchColOfEmptySpace(boardState, cellOfEmptySpace));
            moveSequence.append(moveEmptySpaceToRow(boardState, cellOfEmptySpace, lowerEndOfCycle));
        }

        highestRowWithWhite++;
        phase3_iterations--;
    }

    for (int i = 0; i < moveSequence.size(); i++) {
        if (moveSequence[i] == 'R' && moveSequence[i + 1] == 'L') {
            moveSequence.erase(i, 2);
        }
    }
    return moveSequence;
}