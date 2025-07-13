
#include "generateBoardState.h"
#include "../general.h"
#include <random>
#include <algorithm>

namespace num {

    std::vector<int> generateSolvableBoardState(int n) {

        std::vector<int> boardState (2 * n);

        do {
            boardState = generateBoardState(n);
        } while (!isBoardStateSolvable(boardState));

        return boardState;
    }

    std::vector<int> generateBoardState(int n) {

        std::vector<int> boardState (2 * n);

        boardState[0] = 0;

        for (int i = 1; i < boardState.size(); i++) {
            boardState[i] = i;
        }

        std::random_device randomDevice;
        std::mt19937 generator(randomDevice());

        std::shuffle(boardState.begin(), boardState.end(), generator);

        return boardState;
    }

    bool isBoardStateSolvable(std::vector<int> boardState) {

        int n = boardState.size() / 2;

        int cellOfEmptySpace = getCellOfEmptySpace(boardState);

        // Distance between the empty space's cell and the bottom right square where it belongs.
        int emptySpaceDistance = (1 - getColOfCell(cellOfEmptySpace)) + (n - 1 - getRowOfCell(cellOfEmptySpace));

        // emptySpaceParity is 0 or 1, and it tells us if the amount of moves it takes to solve the board is even or odd respectively.
        bool emptySpaceParity = emptySpaceDistance % 2;

        // Relabel the empty space to be the largest number so that QuickSort puts it to the end of the array.
        boardState[cellOfEmptySpace] = 2 * n;

        return quickSort_countSwaps(boardState, 0, 2 * n - 1) % 2 == emptySpaceParity;
    }

    bool isBoardStateSolvable_slotNotation(const std::vector<int> &boardState) {

        int n = boardState.size() / 2;

        // Create new board state array with renumbered cell numbers according to Section 2.2.1.
        std::vector<int> boardState_snakeLike (boardState.size() + 1);
        // Index 0 is irrelevant - we start with index 1.
        boardState_snakeLike[0] = -1;

        for (int row = 0; row < n; row++) {
            if (row % 2 == 0) {
                boardState_snakeLike[2 * row + 1] = boardState[2 * row];
                boardState_snakeLike[2 * row + 2] = boardState[2 * row + 1];
            } else {
                boardState_snakeLike[2 * row + 1] = boardState[2 * row + 1];
                boardState_snakeLike[2 * row + 2] = boardState[2 * row];
            }
        }

        std::vector<int> boardState_slotNotation (boardState.size() - 1);
        int cellOfEmptySpace = getCellOfEmptySpace(boardState_snakeLike);

        for (int i = 0; i < boardState_slotNotation.size(); i++) {
            for (int j = 1; j < boardState_snakeLike.size(); j++) {
                if (boardState_snakeLike[j] == i + 1) {
                    boardState_slotNotation[i] = j - (j > cellOfEmptySpace);
                }
            }
        }

        int swaps = quickSort_countSwaps(boardState_slotNotation, 0, boardState_slotNotation.size() - 1);

        /* The target state array in slot notation is not exactly the sorted sequence that QuickSort calculates.
            Rows 1, 3, 5 and so on are reversed in slot notation, so we have to add swaps for each of these rows. */
        swaps += floor((n - 1) / 2);

        return swaps % 2 == 0;
    }

    int quickSort_countSwaps(std::vector<int>& vector, int left, int right) {

        if (left < right) {
            int swaps = 0;

            std::random_device randomDevice;
            std::mt19937 generator(randomDevice());
            std::uniform_int_distribution<> dist(left, right);

            int pivotIndex = dist(generator);
            int pivot = vector[pivotIndex];

            int l = left - 1;
            int r = right;

            if (pivotIndex != right) {
                std::swap(vector[pivotIndex], vector[right]);
                swaps++;
            }

            while (l < r) {

                while (vector[++l] < pivot) {}
                while (vector[--r] > pivot && r > left) {}

                if (l < r) {
                    std::swap(vector[l], vector[r]);
                    swaps++;
                }
            }
            if (right != l) {
                std::swap(vector[right], vector[l]);
                swaps++;
            }

            return swaps + quickSort_countSwaps(vector, left, l - 1) + quickSort_countSwaps(vector, l + 1, right);
        }
        return 0;
    }


}

