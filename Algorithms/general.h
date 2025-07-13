
#ifndef GENERAL_H
#define GENERAL_H

#include <vector>
#include <memory>

// Returns the row number of the given cell.
int getRowOfCell(int cell);
// Returns the column number of the given cell.
int getColOfCell(int cell);

// Returns the lowest numbered cell that contains a tile with the given label.
int getCellOfTile(std::vector<int> boardState, int label);

// Returns the cell that the empty space occupies.
int getCellOfEmptySpace(std::vector<int> boardState);

// Returns the target state of the given board state.
std::vector<int> getTargetState(const std::vector<int>& boardState);

// Checks whether the given row contains the given label.
bool rowContainsLabel(std::vector<int> boardState, int row, int label);

// Applies the given move to the board state.
void applyMove(std::vector<int>& boardState, int& cellOfEmptySpace, char direction);
// Applies the given move sequence to the board state.
void applyMoveSequence(std::vector<int>& boardState, int& cellOfEmptySpace, std::string moveSequence);

// Checks whether the given move is valid.
bool isMoveValid(std::vector<int>& boardState, int& cellOfEmptySpace, char direction);
// Checks whether the given move sequence is valid.
bool isMoveSequenceValid(std::vector<int>& boardState, int& cellOfEmptySpace, std::string moveSequence);

// Switches the column of the empty space.
std::string switchColOfEmptySpace(std::vector<int> &boardState, int &cellOfEmptySpace);

// Moves the empty space to the given row using only vertical moves.
std::string moveEmptySpaceToRow(std::vector<int> &boardState, int &cellOfEmptySpace, int row);

// Moves the empty space to the given column using one horizontal move.
std::string moveEmptySpaceToCol(std::vector<int> &boardState, int &cellOfEmptySpace, int col);

// The empty space is moved first vertically, then horizontally to the given cell.
std::string rowFirst_moveEmptySpaceToCell(std::vector<int> &boardState, int &cellOfEmptySpace, int cell);

// The empty space is moved first horizontally, then vertically to the given cell.
std::string colFirst_moveEmptySpaceToCell(std::vector<int> &boardState, int &cellOfEmptySpace, int cell);


#endif //GENERAL_H
