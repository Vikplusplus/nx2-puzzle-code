
#ifndef OPTIMALSOLUTION_H
#define OPTIMALSOLUTION_H
#include "general.h"

struct Node {
    std::vector<int> boardState;
    std::shared_ptr<Node> parent;
    char direction;

    Node(std::vector<int> boardState, std::shared_ptr<Node> parentNode, char direction);
};

struct BoardStateHash {
    size_t operator()(const std::vector<int>& v) const;
};

// Finds the shortest move sequence for getting from the given board state to its target state using a brute-force approach.
std::string optimalSolution(std::vector<int>& boardState);

// Finds the shortest move sequence for getting from the given board state to the given target state using a brute-force approach.
std::string optimalSolution(std::vector<int>& boardState, const std::vector<int>& targetState);


#endif //OPTIMALSOLUTION_H
