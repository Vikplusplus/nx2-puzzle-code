
#ifndef PARTITION_H
#define PARTITION_H
#include "general.h"

// The tiles labeled 1 are placed at the top and the tiles labeled 2 at the bottom of the board.
std::string partition_topToBottom(std::vector<int>& boardState);

// The tiles labeled 1 are placed at the top and the tiles labeled 2 at the bottom of the board.
std::string partition_bottomToTop(std::vector<int>& boardState);

#endif //PARTITION_H
