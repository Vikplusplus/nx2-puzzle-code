
#ifndef TWOCOLOR_GENERATEBOARDSTATE_H
#define TWOCOLOR_GENERATEBOARDSTATE_H

#include <vector>

namespace twoClr {

    // Generates a random 2-color board state with n rows and the given number of tiles labeled one.
    std::vector<int> generateBoardState(int n, int amountOfOnes);

    // Generates a random 2-color board state with n rows and a uniformly random number of tiles labeled one.
    std::vector<int> generateBoardState_uniform(int n);
    // Generates a random 2-color board state with n rows and a binomially random number of tiles labeled one.
    std::vector<int> generateBoardState_binomial(int n, double p);

}


#endif //TWOCOLOR_GENERATEBOARDSTATE_H
