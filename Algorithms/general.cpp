
#include "general.h"
#include <cmath>
#include <utility>

int getRowOfCell(int cell) {
    return floor(cell / 2);
}

int getColOfCell(int cell) {
    return cell % 2;
}

int getCellOfTile(std::vector<int> boardState, int label) {

    for (int i = 0; i < boardState.size(); i++) {
        if (boardState[i] == label) return i;
    }
    return -1;
}

int getCellOfEmptySpace(std::vector<int> boardState) {
    return getCellOfTile(std::move(boardState), 0);
}

std::vector<int> getTargetState(const std::vector<int>& boardState) {
    int n = boardState.size() / 2;

    std::vector<int> targetState (2 * n);

    int label = 1;
    int cell = 0;

    while (cell < 2 * n - 1) {

        int labelCount = 0;

        for (int i : boardState) {
            if (i == label) labelCount++;
        }

        if (labelCount == 0) break;

        for (int i = 0; i < labelCount; i++) {
            targetState[cell + i] = label;
        }

        cell += labelCount;
        label++;
    }

    targetState[2 * n - 1] = 0;

    return targetState;
}

bool rowContainsLabel(std::vector<int> boardState, int row, int label) {
    return boardState[2 * row] == label || boardState[2 * row + 1] == label;
}

void applyMove(std::vector<int>& boardState, int& cellOfEmptySpace, char direction) {
    int n = boardState.size() / 2;

    int rowOfEmptySpace = getRowOfCell(cellOfEmptySpace);
    int colOfEmptySpace = getColOfCell(cellOfEmptySpace);

    if (rowOfEmptySpace < n - 1 && direction == 'U') {
        std::swap(boardState[cellOfEmptySpace], boardState[cellOfEmptySpace + 2]);
        cellOfEmptySpace += 2;
    }
    else if (rowOfEmptySpace > 0 && direction == 'D') {
        std::swap(boardState[cellOfEmptySpace], boardState[cellOfEmptySpace - 2]);
        cellOfEmptySpace -= 2;
    }
    else if (colOfEmptySpace == 0 && direction == 'L') {
        std::swap(boardState[cellOfEmptySpace], boardState[cellOfEmptySpace + 1]);
        cellOfEmptySpace++;
    }
    else if (colOfEmptySpace == 1 && direction == 'R') {
        std::swap(boardState[cellOfEmptySpace], boardState[cellOfEmptySpace - 1]);
        cellOfEmptySpace--;
    }
}

void applyMoveSequence(std::vector<int>& boardState, int& cellOfEmptySpace, std::string moveSequence) {
    for (int i = 0; i < moveSequence.length(); i++) {
        applyMove(boardState, cellOfEmptySpace, moveSequence[i]);
    }
}

bool isMoveValid(std::vector<int> &boardState, int &cellOfEmptySpace, char direction) {
    int n = boardState.size() / 2;

    int rowOfEmptySpace = getRowOfCell(cellOfEmptySpace);
    int colOfEmptySpace = getColOfCell(cellOfEmptySpace);

    return (direction == 'U' && rowOfEmptySpace < n - 1 ||
            direction == 'D' && rowOfEmptySpace > 0 ||
            direction == 'L' && colOfEmptySpace == 0 ||
            direction == 'R' && colOfEmptySpace == 1);
}

bool isMoveSequenceValid(std::vector<int> &boardState, int &cellOfEmptySpace, std::string moveSequence) {

    bool moveSequenceIsLegal = true;
    for (char direction : moveSequence) {
        if (!isMoveValid(boardState, cellOfEmptySpace, direction)) {
            moveSequenceIsLegal = false;
            break;
        }
        applyMove(boardState, cellOfEmptySpace, direction);
    }
    return moveSequenceIsLegal;
}

std::string switchColOfEmptySpace(std::vector<int> &boardState, int &cellOfEmptySpace) {

    int colOfEmptySpace = getColOfCell(cellOfEmptySpace);

    char direction = (colOfEmptySpace == 0) ? 'L' : 'R';

    applyMove(boardState, cellOfEmptySpace, direction);

    return std::string(1, direction);
}

std::string moveEmptySpaceToRow(std::vector<int> &boardState, int &cellOfEmptySpace, int row) {

    int rowOfEmptySpace = getRowOfCell(cellOfEmptySpace);

    char direction = (rowOfEmptySpace < row) ? 'U' : 'D';
    int distance = abs(rowOfEmptySpace - row);

    for (int i = 0; i < distance; i++) {
        applyMove(boardState, cellOfEmptySpace, direction);
    }

    return std::string(distance, direction);
}

std::string moveEmptySpaceToCol(std::vector<int> &boardState, int &cellOfEmptySpace, int col) {

    int colOfEmptySpace = getColOfCell(cellOfEmptySpace);

    if (col != colOfEmptySpace) return switchColOfEmptySpace(boardState, cellOfEmptySpace);

    return "";
}

// The empty space moves first vertically, then horizontally to the given cell.
std::string rowFirst_moveEmptySpaceToCell(std::vector<int> &boardState, int &cellOfEmptySpace, int cell) {

    std::string moveSequence;

    int rowOfCell = getRowOfCell(cell);
    int colOfCell = getColOfCell(cell);

    moveSequence.append(moveEmptySpaceToRow(boardState, cellOfEmptySpace, rowOfCell));
    moveSequence.append(moveEmptySpaceToCol(boardState, cellOfEmptySpace, colOfCell));

    return moveSequence;
}

// The empty space moves first horizontally, then vertically to the given cell.
std::string colFirst_moveEmptySpaceToCell(std::vector<int> &boardState, int &cellOfEmptySpace, int cell) {

    std::string moveSequence;

    int rowOfCell = getRowOfCell(cell);
    int colOfCell = getColOfCell(cell);

    moveSequence.append(moveEmptySpaceToCol(boardState, cellOfEmptySpace, colOfCell));
    moveSequence.append(moveEmptySpaceToRow(boardState, cellOfEmptySpace, rowOfCell));

    return moveSequence;
}

