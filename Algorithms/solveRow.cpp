
#include "solveRow.h"

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

    if (!rowContainsLabel(boardState, row, label)) {

        int cellOfFirstTarget = 2 * (row + 1);
        while (cellOfFirstTarget <= boardState.size() && boardState[cellOfFirstTarget] != label) cellOfFirstTarget++;


        if (getColOfCell(cellOfFirstTarget) == 0 && boardState[cellOfFirstTarget + 1] == label) {
            if (
                (getRowOfCell(cellOfEmptySpace) < getRowOfCell(cellOfFirstTarget) && getColOfCell(cellOfEmptySpace) == 1) ||
                (getRowOfCell(cellOfEmptySpace > getRowOfCell(cellOfFirstTarget)) && getColOfCell(cellOfEmptySpace) == 0)) {
                cellOfFirstTarget++;
            }
        }
        if (getRowOfCell(cellOfEmptySpace) > getRowOfCell(cellOfFirstTarget) &&
            getColOfCell(cellOfEmptySpace) == getColOfCell(cellOfFirstTarget)) {
            moveSequence.append(switchColOfEmptySpace(boardState, cellOfEmptySpace));
        }

        moveSequence.append(rowFirst_moveEmptySpaceToCell(boardState, cellOfEmptySpace, cellOfFirstTarget - 2));
        applyMove(boardState, cellOfEmptySpace, 'U');
        moveSequence.append("U");

        moveSequence.append(liftTile(boardState, cellOfEmptySpace, row));
    }

    if (boardState[2 * row] == label && boardState[2 * row + 1] == label) return moveSequence;

    int targetColumn = (boardState[2 * row] == label) ? 0 : 1;

    if (getRowOfCell(cellOfEmptySpace) == row && boardState[cellOfEmptySpace + 2] == label) {
        applyMove(boardState, cellOfEmptySpace, 'U');
        moveSequence.append("U");
        return moveSequence;
    }
    if (boardState[2 * (row + 1) + targetColumn] != label) {

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
                if (targetColumn == 1) closestTarget++;
            }

            if (getColOfCell(closestTarget) != targetColumn) {
                moveSequence.append(colFirst_moveEmptySpaceToCell(boardState, cellOfEmptySpace, 2 * getRowOfCell(closestTarget) + targetColumn));
                moveSequence.append(switchColOfEmptySpace(boardState, cellOfEmptySpace));
                closestTarget = (targetColumn == 1) ? (closestTarget + 1) : (closestTarget - 1);
            }
            if (getRowOfCell(cellOfEmptySpace) > getRowOfCell(closestTarget) &&
                getColOfCell(cellOfEmptySpace) == getColOfCell(closestTarget)) {
                moveSequence.append(switchColOfEmptySpace(boardState, cellOfEmptySpace));
            }
            moveSequence.append(rowFirst_moveEmptySpaceToCell(boardState, cellOfEmptySpace, closestTarget - 2));

            applyMove(boardState, cellOfEmptySpace, 'U');
            moveSequence.append("U");

            moveSequence.append(liftTile(boardState, cellOfEmptySpace, row + 1));

        }
    }
    moveSequence.append(colFirst_moveEmptySpaceToCell(boardState, cellOfEmptySpace, 2 * row + 1 - targetColumn));
    moveSequence.append(switchColOfEmptySpace(boardState, cellOfEmptySpace));
    applyMove(boardState, cellOfEmptySpace, 'U');
    moveSequence.append("U");

    return moveSequence;

}

std::string solveRow_diffLabels(std::vector<int> &boardState, int &cellOfEmptySpace, int row, int label1, int label2) {

    if (boardState[2 * row + 1] == label2) {
        if (boardState[2 * row] == label1) return "";

        if (cellOfEmptySpace == 2 * row && boardState[2 * (row + 1)] == label1) {
            applyMove(boardState, cellOfEmptySpace, 'U');
            return "U";
        }
    }
    std::string moveSequence;

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

        if (target == 2 * row) {
            moveSequence.append(colFirst_moveEmptySpaceToCell(boardState, cellOfEmptySpace, 2 * row + 1));
            moveSequence.append(switchColOfEmptySpace(boardState, cellOfEmptySpace));
        }
        else {
            if (getColOfCell(target) == 0) {
                moveSequence.append(colFirst_moveEmptySpaceToCell(boardState, cellOfEmptySpace, target + 1));
                moveSequence.append(switchColOfEmptySpace(boardState, cellOfEmptySpace));
                target++;
            }
            if (getColOfCell(cellOfEmptySpace) == 1 && cellOfEmptySpace > target) {
                moveSequence.append(switchColOfEmptySpace(boardState,cellOfEmptySpace));
            }

            moveSequence.append(rowFirst_moveEmptySpaceToCell(boardState, cellOfEmptySpace, target - 2));

            applyMove(boardState, cellOfEmptySpace, 'U');
            moveSequence.append("U");

            moveSequence.append(liftTile(boardState, cellOfEmptySpace, row));
        }
    }

    if (boardState[2 * row] == label2) {
        moveSequence.append(colFirst_moveEmptySpaceToCell(boardState, cellOfEmptySpace, 2 * row));

        applyMoveSequence(boardState, cellOfEmptySpace, "LUURDLDRUULDRDLU");
        moveSequence.append("LUURDLDRUULDRDLU");

        return moveSequence;
    }
    target = 2 * row + 2;
    while (target <= boardState.size() && boardState[target] != label2) target++;

    if (getColOfCell(target) == 0 && boardState[target + 1] == label2) target++;

    if (target != 2 * (row + 1) + 1) {

        if (target == 2 * (row + 1)) {

            if (cellOfEmptySpace == 2 * row) {
                applyMoveSequence(boardState, cellOfEmptySpace, "LUURDLDRUULDRDLU");
                moveSequence.append("LUURDLDRUULDRDLU");

                return moveSequence;
            }
            moveSequence.append(colFirst_moveEmptySpaceToCell(boardState, cellOfEmptySpace, target + 1));
            moveSequence.append(switchColOfEmptySpace(boardState, cellOfEmptySpace));
        }
        else {
            if (cellOfEmptySpace == 2 * row) {
                applyMove(boardState, cellOfEmptySpace, 'U');
                moveSequence.append("U");
            }

            if (getColOfCell(target) == 0) {
                moveSequence.append(colFirst_moveEmptySpaceToCell(boardState, cellOfEmptySpace, target + 1));
                moveSequence.append(switchColOfEmptySpace(boardState, cellOfEmptySpace));
                target++;
            }
            if (getColOfCell(cellOfEmptySpace) == 1 && cellOfEmptySpace > target) {
                moveSequence.append(switchColOfEmptySpace(boardState,cellOfEmptySpace));
            }
            moveSequence.append(rowFirst_moveEmptySpaceToCell(boardState, cellOfEmptySpace, target - 2));

            applyMove(boardState, cellOfEmptySpace, 'U');
            moveSequence.append("U");

            moveSequence.append(liftTile(boardState, cellOfEmptySpace, row + 1));
        }
    }
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
    moveSequence.append(switchColOfEmptySpace(boardState, cellOfEmptySpace));

    applyMoveSequence(boardState, cellOfEmptySpace, "DD");
    moveSequence.append("DD");

    moveSequence.append(switchColOfEmptySpace(boardState, cellOfEmptySpace));

    applyMove(boardState, cellOfEmptySpace, 'U');
    moveSequence.append("U");

    return moveSequence;
}
