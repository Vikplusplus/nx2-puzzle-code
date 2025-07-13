
#include "generateBoardState.h"
#include <random>
#include <algorithm>
#include <iostream>

namespace kClr {

    std::vector<int> generateBoardState(int n, int k) {

        if (k < 3 || k > 2 * n - 2) return generateBoardState_binomial(n, 0.5);

        std::vector<int> boardState (2 * n);

        for (int c = 0; c <= k; c++) {
            boardState[c] = c;
        }

        std::random_device randomDevice;
        std::mt19937 generator(randomDevice());
        std::uniform_int_distribution<> dist(1, k);

        for (int i = k + 1; i <= 2 * n - 1; i++) {
            boardState[i] = dist(generator);
        }

        std::shuffle(boardState.begin(), boardState.end(), generator);

        return boardState;
    }

    std::vector<int> generateBoardState_binomial(int n, double p) {
        std::random_device randomDevice;
        std::mt19937 generator(randomDevice());

        int t = 2 * n - 3;

        std::binomial_distribution<> dist(t, p);

        int k = dist(generator) + 1;

        return generateBoardState(n, k);
    }

}
