
#ifndef KCOLOR_GENERATEBOARDSTATE_H
#define KCOLOR_GENERATEBOARDSTATE_H
#include "../general.h"

namespace kClr {

    // Generates a random k-color board state with n rows where each tile occurs k/n times in expectation.
    std::vector<int> generateBoardState(int n, int k);

    // Generates a random k-color board state with n rows and expected k = p * n.
    std::vector<int> generateBoardState_binomial(int n, double p);

}
#endif //KCOLOR_GENERATEBOARDSTATE_H
