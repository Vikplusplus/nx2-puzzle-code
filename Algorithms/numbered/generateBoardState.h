
#ifndef NUMBERED_GENERATEBOARDSTATE_H
#define NUMBERED_GENERATEBOARDSTATE_H
#include <vector>

namespace num {

    // Generates a random solvable numbered board state with n rows.
    std::vector<int> generateSolvableBoardState(int n);

    // Generates a random board state with n rows.
    std::vector<int> generateBoardState(int n);

    // Checks whether a given board state can be solved.
    bool isBoardStateSolvable(std::vector<int>boardState);

    // Checks whether a given board state can be solved using its slot notation.
    bool isBoardStateSolvable_slotNotation(const std::vector<int>& boardState);

    // Uses Quick Sort on the given vector while counting the amount of swaps.
    int quickSort_countSwaps(std::vector<int>& vector, int left, int right);

}

#endif //NUMBERED_GENERATEBOARDSTATE_H
