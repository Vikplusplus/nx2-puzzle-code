
#include "solveRow.h"

#include <iostream>

std::string solveRow(std::vector<int> &boardState, int &cellOfEmptySpace, int row, int label1, int label2) {

    std::string moveSequence;

    if (label1 == label2) {
        moveSequence.append(solveRow_sameLabels(boardState, cellOfEmptySpace, row, label1));
    }
    else {
        moveSequence.append(solveRow_diffLabels(boardState, cellOfEmptySpace, row, label1, label2));
    }

    return moveSequence;
}

std::string solveRow_sameLabels(std::vector<int> &boardState, int &cellOfEmptySpace, int row, int label) {

    if (boardState[2 * row] == label && boardState[2 * row + 1] == label) return "";

    std::string moveSequence;

    // Put first tile with target label into row
    if (!rowContainsLabel(boardState, row, label)) {

        int cellOfFirstTarget = 2 * (row + 1);
        while (cellOfFirstTarget <= boardState.size() && boardState[cellOfFirstTarget] != label) cellOfFirstTarget++;


        if (getColOfCell(cellOfFirstTarget) == 0 && boardState[cellOfFirstTarget + 1] == label) {
            // If the tile right to firstTarget also has the target label, we switch to
            // targeting the tile to the right depending on the position of the empty space.
            if (
                (getRowOfCell(cellOfEmptySpace) < getRowOfCell(cellOfFirstTarget) && getColOfCell(cellOfEmptySpace) == 1) ||
                (getRowOfCell(cellOfEmptySpace > getRowOfCell(cellOfFirstTarget)) && getColOfCell(cellOfEmptySpace) == 0)) {
                cellOfFirstTarget++;
            }
        }
        // If the empty space is below firstTarget and in the same column, move the empty space horizontally.
        if (getRowOfCell(cellOfEmptySpace) > getRowOfCell(cellOfFirstTarget) &&
            getColOfCell(cellOfEmptySpace) == getColOfCell(cellOfFirstTarget)) {
            moveSequence.append(switchColOfEmptySpace(boardState, cellOfEmptySpace));
        }

        // Move the empty space above firstTarget.
        moveSequence.append(rowFirst_moveEmptySpaceToCell(boardState, cellOfEmptySpace, cellOfFirstTarget - 2));
        applyMove(boardState, cellOfEmptySpace, 'U');
        moveSequence.append("U");

        moveSequence.append(liftTile(boardState, cellOfEmptySpace, row));
    }

    if (boardState[2 * row] == label && boardState[2 * row + 1] == label) return moveSequence;

    // Top row now contains one correctly colored tile in targetColumn.
    int targetColumn = (boardState[2 * row] == label) ? 0 : 1;

    if (getRowOfCell(cellOfEmptySpace) == row && boardState[cellOfEmptySpace + 2] == label) {
        applyMove(boardState, cellOfEmptySpace, 'U');
        moveSequence.append("U");
        return moveSequence;
    }
    // Put another tile with target label below first the one.
    if (boardState[2 * (row + 1) + targetColumn] != label) {

        // If a target tile is already in the correct row but in the wrong column.
        if (boardState[2 * (row + 1) + 1 - targetColumn] == label) {
            moveSequence.append(colFirst_moveEmptySpaceToCell(boardState, cellOfEmptySpace, 2 * (row + 1) + targetColumn));
            moveSequence.append(switchColOfEmptySpace(boardState, cellOfEmptySpace));
        }
        else {

            if (getRowOfCell(cellOfEmptySpace) == row) {
                applyMove(boardState, cellOfEmptySpace, 'U');
                moveSequence.append("U");
            }

            int closestTarget = 2 * (row + 2);

            while (closestTarget <= boardState.size() && boardState[closestTarget] != label) closestTarget++;
            if (getColOfCell(closestTarget) == 0 && boardState[closestTarget + 1] == label) {
                // Switch to targeting the tile in the right column depending on the position of the empty space.
                if (targetColumn == 1) closestTarget++;
            }

            // Move the target tile into the correct column.
            if (getColOfCell(closestTarget) != targetColumn) {
                moveSequence.append(colFirst_moveEmptySpaceToCell(boardState, cellOfEmptySpace, 2 * getRowOfCell(closestTarget) + targetColumn));
                moveSequence.append(switchColOfEmptySpace(boardState, cellOfEmptySpace));
                closestTarget = (targetColumn == 1) ? (closestTarget + 1) : (closestTarget - 1);
            }
            // If the empty space is below the target and in the same column, move the empty space horizontally.
            if (getRowOfCell(cellOfEmptySpace) > getRowOfCell(closestTarget) &&
                getColOfCell(cellOfEmptySpace) == getColOfCell(closestTarget)) {
                moveSequence.append(switchColOfEmptySpace(boardState, cellOfEmptySpace));
            }
            // Move the empty space above the target tile.
            moveSequence.append(rowFirst_moveEmptySpaceToCell(boardState, cellOfEmptySpace, closestTarget - 2));

            applyMove(boardState, cellOfEmptySpace, 'U');
            moveSequence.append("U");

            moveSequence.append(liftTile(boardState, cellOfEmptySpace, row + 1));

        }
    }
    // Complete solving the row.
    moveSequence.append(colFirst_moveEmptySpaceToCell(boardState, cellOfEmptySpace, 2 * row + 1 - targetColumn));
    moveSequence.append(switchColOfEmptySpace(boardState, cellOfEmptySpace));
    applyMove(boardState, cellOfEmptySpace, 'U');
    moveSequence.append("U");

    return moveSequence;

}

std::string solveRow_diffLabels(std::vector<int> &boardState, int &cellOfEmptySpace, int row, int label1, int label2) {

    // Some cases where the row can quickly be solved.
    if (boardState[2 * row + 1] == label2) {
        if (boardState[2 * row] == label1) return "";

        if (cellOfEmptySpace == 2 * row && boardState[2 * (row + 1)] == label1) {
            applyMove(boardState, cellOfEmptySpace, 'U');
            return "U";
        }
    }
    std::string moveSequence;

    // Some more exceptions where solving the row is possible quickly.
    if (boardState[2 * row] == label1) {

        if (cellOfEmptySpace == 2 * row + 1 && boardState[2 * (row + 1) + 1] == label2) {
            applyMove(boardState, cellOfEmptySpace, 'U');
            return "U";
        }
        if (boardState[2 * (row + 1)] == label2) {

            moveSequence.append(rowFirst_moveEmptySpaceToCell(boardState, cellOfEmptySpace, 2 * (row + 2)));

            applyMoveSequence(boardState, cellOfEmptySpace, "DLDRUULDRDLU");
            moveSequence.append("DLDRUULDRDLU");
            return moveSequence;
        }
        if (boardState[2 * (row + 1) + 1] == label2) {
            moveSequence.append(rowFirst_moveEmptySpaceToCell(boardState, cellOfEmptySpace, 2 * (row + 2) + 1));

            applyMoveSequence(boardState, cellOfEmptySpace, "DDRULURDDLU");
            moveSequence.append("DDRULURDDLU");
            return moveSequence;
        }

    }

    int target = 2 * row;
    while (target <= boardState.size() && boardState[target] != label1) target++;

    if (target != 2 * row + 1) {

        // Move the first target away from its target cell so that the row can more easily be solved later.
        if (target == 2 * row) {
            moveSequence.append(colFirst_moveEmptySpaceToCell(boardState, cellOfEmptySpace, 2 * row + 1));
            moveSequence.append(switchColOfEmptySpace(boardState, cellOfEmptySpace));
        }
        else {
            // Move the target tile into the right column.
            if (getColOfCell(target) == 0) {
                moveSequence.append(colFirst_moveEmptySpaceToCell(boardState, cellOfEmptySpace, target + 1));
                moveSequence.append(switchColOfEmptySpace(boardState, cellOfEmptySpace));
                target++;
            }
            // If the empty space is below the target and in the same column, move the empty space horizontally.
            if (getColOfCell(cellOfEmptySpace) == 1 && cellOfEmptySpace > target) {
                moveSequence.append(switchColOfEmptySpace(boardState,cellOfEmptySpace));
            }

            // Move the empty space above the target tile.
            moveSequence.append(rowFirst_moveEmptySpaceToCell(boardState, cellOfEmptySpace, target - 2));

            applyMove(boardState, cellOfEmptySpace, 'U');
            moveSequence.append("U");

            moveSequence.append(liftTile(boardState, cellOfEmptySpace, row));
        }
    }
    // The tile in cell (2 * row + 1) is now labeled with label1.

    // If the target row is in opposite order, apply a special move sequence.
    if (boardState[2 * row] == label2) {
        moveSequence.append(colFirst_moveEmptySpaceToCell(boardState, cellOfEmptySpace, 2 * row));

        applyMoveSequence(boardState, cellOfEmptySpace, "LUURDLDRUULDRDLU");
        moveSequence.append("LUURDLDRUULDRDLU");

        return moveSequence;
    }
    target = 2 * row + 2;
    while (target <= boardState.size() && boardState[target] != label2) target++;

    // This is only relevant in the 2-color and k-color variations.
    if (getColOfCell(target) == 0 && boardState[target + 1] == label2) target++;

    if (target != 2 * (row + 1) + 1) {

        if (target == 2 * (row + 1)) {

            if (cellOfEmptySpace == 2 * row) {
                applyMoveSequence(boardState, cellOfEmptySpace, "LUURDLDRUULDRDLU");
                moveSequence.append("LUURDLDRUULDRDLU");

                return moveSequence;
            }
            // If the target tile is already in the correct row but in the wrong column.
            moveSequence.append(colFirst_moveEmptySpaceToCell(boardState, cellOfEmptySpace, target + 1));
            moveSequence.append(switchColOfEmptySpace(boardState, cellOfEmptySpace));
        }
        else {
            if (cellOfEmptySpace == 2 * row) {
                applyMove(boardState, cellOfEmptySpace, 'U');
                moveSequence.append("U");
            }

            // Move the target tile into the correct column.
            if (getColOfCell(target) == 0) {
                moveSequence.append(colFirst_moveEmptySpaceToCell(boardState, cellOfEmptySpace, target + 1));
                moveSequence.append(switchColOfEmptySpace(boardState, cellOfEmptySpace));
                target++;
            }
            // If the empty space is below the target and in the same column, move the empty space horizontally.
            if (getColOfCell(cellOfEmptySpace) == 1 && cellOfEmptySpace > target) {
                moveSequence.append(switchColOfEmptySpace(boardState,cellOfEmptySpace));
            }
            // Move the empty space above firstTarget.
            moveSequence.append(rowFirst_moveEmptySpaceToCell(boardState, cellOfEmptySpace, target - 2));

            applyMove(boardState, cellOfEmptySpace, 'U');
            moveSequence.append("U");

            moveSequence.append(liftTile(boardState, cellOfEmptySpace, row + 1));
        }
    }
    // Complete solving the row.
    moveSequence.append(colFirst_moveEmptySpaceToCell(boardState, cellOfEmptySpace, 2 * row));

    applyMoveSequence(boardState, cellOfEmptySpace, "LU");
    moveSequence.append("LU");

    return moveSequence;
}

std::string liftTile(std::vector<int> &boardState, int &cellOfEmptySpace, int row) {
    std::string moveSequence;

    int distance = getRowOfCell(cellOfEmptySpace) - 1 - row;

    for (int i = 0; i < distance; i++) {
        moveSequence.append(liftTileByOneRow(boardState, cellOfEmptySpace));
    }

    return moveSequence;
}

std::string liftTileByOneRow(std::vector<int> &boardState, int &cellOfEmptySpace) {

    std::string moveSequence;
    // Go around the target tile and then move it up.
    moveSequence.append(switchColOfEmptySpace(boardState, cellOfEmptySpace));

    applyMoveSequence(boardState, cellOfEmptySpace, "DD");
    moveSequence.append("DD");

    moveSequence.append(switchColOfEmptySpace(boardState, cellOfEmptySpace));

    applyMove(boardState, cellOfEmptySpace, 'U');
    moveSequence.append("U");

    return moveSequence;
}
