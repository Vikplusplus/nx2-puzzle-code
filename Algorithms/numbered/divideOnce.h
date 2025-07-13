
#ifndef NUMBERED_DIVIDEONCE_H
#define NUMBERED_DIVIDEONCE_H
#include "../general.h"

namespace num {

    // Solves the puzzle by first presorting each tile into its correct board half and then solving each row iteratively.
    std::string divideOnce(std::vector<int>& boardState);
}

#endif //NUMBERED_DIVIDEONCE_H
