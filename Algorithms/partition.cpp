
#include "partition.h"
#include <cmath>
#include <iostream>


std::string partition_topToBottom(std::vector<int>& boardState) {
    int n = boardState.size() / 2;

    int cellOfEmptySpace = getCellOfEmptySpace(boardState);

    std::string moveSequence;

    moveSequence.append(moveEmptySpaceToCol(boardState, cellOfEmptySpace, 1));

    int highestRowWithWhite = 0;
    while (!rowContainsLabel(boardState, highestRowWithWhite, 2)) highestRowWithWhite++;

    int lowerEndOfCycle = highestRowWithWhite;
    // Search for first black tile in right column that is in highestRowWithWhite or below.
    while (lowerEndOfCycle <= n - 1 && boardState[2 * lowerEndOfCycle + 1] != 1) lowerEndOfCycle++;

    bool emptySpaceAbove = getRowOfCell(cellOfEmptySpace) < lowerEndOfCycle;

    // If the empty space is in a row above lowerEndOfCycle,
    // move it to row (lowerEndOfCycle - 1).
    moveSequence.append(moveEmptySpaceToRow(
        boardState, cellOfEmptySpace, lowerEndOfCycle - emptySpaceAbove));

    // If the empty space was below lowerEndOfCycle, the tile in cell
    // (2 * lowerEndOfCycle + 1) was moved down one row -> Increase upperEndOfCycle.
    lowerEndOfCycle += !emptySpaceAbove;

    // Decrease highestRowWithWhite if it got decreased during the moves before.
    if (highestRowWithWhite > 0 && rowContainsLabel(boardState, highestRowWithWhite - 1, 2)) highestRowWithWhite--;

    // Phase 1 -> Push all black tiles that are in the right column below highestRowWithWhite to the left.
    while (lowerEndOfCycle <= n - 1) {

        int upperEndOfCycle = highestRowWithWhite;

        // If highestRowWithWhite also contains a black tile in column 1, the cycle move sequence can not be applied.
        if (boardState[2 * upperEndOfCycle] == 2 && boardState[2 * upperEndOfCycle + 1] == 1){
            moveSequence.append(moveEmptySpaceToRow(boardState, cellOfEmptySpace, upperEndOfCycle));

            while (lowerEndOfCycle <= n - 1 && boardState[2 * lowerEndOfCycle + 1] != 1) {
                lowerEndOfCycle++;
            }
            continue;
        }

        // Search for the first row below highestRowWithWhite that contains a black tile.
        while (upperEndOfCycle < lowerEndOfCycle - 1) {
            if (rowContainsLabel(boardState, upperEndOfCycle + 1, 1)) break;
            upperEndOfCycle++;
        }

        // Phase 1 cycle move sequence.
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

    // Phase 2 -> Push all white tiles that are in the left column above lowestRowWithBlack to the right column.
    while (upperEndOfCycle >= 0) {
        // There are no more white tiles above upperEndOfCycle in this case.
        if (boardState[2 * upperEndOfCycle + 1] == 1) break;

        // White tile found in left column.
        if (boardState[2 * upperEndOfCycle] == 2) {
            moveSequence.append(moveEmptySpaceToRow(boardState, cellOfEmptySpace, upperEndOfCycle));

            // Phase 2 cycle move sequence.
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

    // Phase 3 -> Complete the partition.
    while (phase3_iterations) {

        int upperEndOfCycle = getRowOfCell(cellOfEmptySpace) + 1;

        // Phase 3 cycle move sequence.
        moveSequence.append(switchColOfEmptySpace(boardState, cellOfEmptySpace));
        moveSequence.append(moveEmptySpaceToRow(boardState, cellOfEmptySpace, lowestRowWithBlack));
        moveSequence.append(switchColOfEmptySpace(boardState, cellOfEmptySpace));
        moveSequence.append(moveEmptySpaceToRow(boardState, cellOfEmptySpace, upperEndOfCycle));

        lowestRowWithBlack--;
        phase3_iterations--;
    }

    // Remove unnecessary "LR" move combinations that occur in some exceptions.
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

    // If the empty space is in a row lower than upperEndOfCycle,
    // move it to row (upperEndOfCycle + 1).
    moveSequence.append(moveEmptySpaceToRow(
        boardState, cellOfEmptySpace, upperEndOfCycle + emptySpaceBelow));

    // If the empty space was above upperEndOfCycle, the tile in cell
    // (2 * upperEndOfCycle) was moved up one row -> Decrease upperEndOfCycle.
    upperEndOfCycle -= !emptySpaceBelow;

    // Increase lowestRowWithBlack if it got increased during the moves before.
    if (lowestRowWithBlack < n - 1 && rowContainsLabel(boardState, lowestRowWithBlack + 1, 1)) lowestRowWithBlack++;

    // Phase 1 -> Push all white tiles that are in the left column above lowestRowWithBlack to the right.
    while (upperEndOfCycle >= 0) {

        int lowerEndOfCycle = lowestRowWithBlack;

        // If lowestRowWithBlack also cointains a white tile in column 1, the cycle move sequence can not be applied.
        if (boardState[2 * lowerEndOfCycle] == 2 && boardState[2 * lowerEndOfCycle + 1] == 1) {
            moveSequence.append(moveEmptySpaceToRow(boardState, cellOfEmptySpace, lowerEndOfCycle));

            while (upperEndOfCycle >= 0 && boardState[2 * upperEndOfCycle] != 2) upperEndOfCycle--;
            continue;
        }

        // Search for the first row above lowestRowWithBlack that contains a white tile.
        while (lowerEndOfCycle > upperEndOfCycle + 1) {
            if (rowContainsLabel(boardState, lowerEndOfCycle - 1, 2)) break;
            lowerEndOfCycle--;
        }

        // Phase 1 cycle move sequence.
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

    // Phase 2 -> Push all black tiles that are in the right column below highestRowWithWhite to the left column.
    while (lowerEndOfCycle <= n - 1) {
        // There are no more black tiles below lowerEndOfCycle in this case.
        if (boardState[2 * lowerEndOfCycle] == 2) break;

        // Black tile found in right column.
        if (boardState[2 * lowerEndOfCycle + 1] == 1) {
            moveSequence.append(moveEmptySpaceToRow(boardState, cellOfEmptySpace, lowerEndOfCycle));

            // Phase 3 cycle move sequence.
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

    // Phase 3 -> Complete the partition.
    while (phase3_iterations) {

        // Phase 3 cycle move sequence.
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

    // Remove unnecessary "RL" move combinations.
    for (int i = 0; i < moveSequence.size(); i++) {
        if (moveSequence[i] == 'R' && moveSequence[i + 1] == 'L') {
            moveSequence.erase(i, 2);
        }
    }
    return moveSequence;
}