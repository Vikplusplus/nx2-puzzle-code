
#ifndef SOLVEROW_H
#define SOLVEROW_H
#include "general.h"


// Solves one row of the puzzle.
std::string solveRow(std::vector<int>& boardState, int& cellOfEmptySpace, int row, int label1, int label2);

// Solves one row of the puzzle where both tiles have the same label in the target state.
std::string solveRow_sameLabels(std::vector<int>& boardState, int& cellOfEmptySpace, int row, int label);

// Solves one row of the puzzle where both tiles have different labels in the target state.
std::string solveRow_diffLabels(std::vector<int>& boardState, int& cellOfEmptySpace, int row, int label1, int label2);

// The tile directly above the empty space is moved to the given row.
std::string liftTile(std::vector<int>& boardState, int& cellOfEmptySpace, int row);

// The tile directly above the empty space is moved up by one row.
std::string liftTileByOneRow(std::vector<int>& boardState, int& cellOfEmptySpace);


#endif //SOLVEROW_H
