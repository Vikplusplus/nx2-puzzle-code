
#include "generateBoardState.h"
#include <random>
#include <algorithm>

namespace twoClr {

    std::vector<int> generateBoardState(int n, int amountOfOnes) {

        if (amountOfOnes < 1 || amountOfOnes > 2 * n - 2) {
            return generateBoardState(n, n);
        }

        std::vector<int> boardState (2 * n);

        boardState[0] = 0;

        for (int i = 1; i <= amountOfOnes; i++) {
            boardState[i] = 1;
        }

        for (int i = amountOfOnes + 1; i < boardState.size(); i++) {
            boardState[i] = 2;
        }

        std::random_device randomDevice;
        std::mt19937 generator(randomDevice());

        std::shuffle(boardState.begin(), boardState.end(), generator);

        return boardState;
    }

    std::vector<int> generateBoardState_uniform(int n) {

        std::random_device randomDevice;
        std::mt19937 generator(randomDevice());
        std::uniform_int_distribution<> dist(1, 2 * n - 2);

        int amountOfOnes = dist(generator);

        return generateBoardState(n, amountOfOnes);
    }

    std::vector<int> generateBoardState_binomial(int n, double p) {

        std::random_device randomDevice;
        std::mt19937 generator(randomDevice());

        int t = 2 * n - 3;

        std::binomial_distribution<> dist(t, p);

        int amountOfOnes = dist(generator) + 1;

        return generateBoardState(n, amountOfOnes);
    }


}


