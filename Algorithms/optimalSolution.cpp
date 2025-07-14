
#include "optimalSolution.h"
#include <queue>
#include <unordered_set>
#include <utility>

Node::Node(std::vector<int> boardState, std::shared_ptr<Node> parent, char direction) {
    this->boardState = std::move(boardState);
    this->parent = std::move(parent);
    this->direction = direction;
}

std::size_t BoardStateHash::operator()(const std::vector<int>& boardState) const {
    std::size_t hash = boardState.size();
    for (int num : boardState) {
        hash ^= std::hash<int>{}(num) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
    }
    return hash;
}

std::string optimalSolution(std::vector<int>& boardState) {

    std::vector<int> targetState = getTargetState(boardState);

    return optimalSolution(boardState, targetState);
}

std::string optimalSolution(std::vector<int> &boardState, const std::vector<int> &targetState) {
    int n = boardState.size() / 2;

    std::queue<Node> queue;

    Node root = Node(boardState, nullptr, '\0');

    queue.push(root);

    std::unordered_set<std::vector<int>, BoardStateHash> visitedBoardStates;

    Node currentNode = root;

    while (!queue.empty()) {

        currentNode = queue.front();
        queue.pop();

        std::vector<int> currentBoardState = currentNode.boardState;

        if (currentBoardState == targetState) break;

        if (visitedBoardStates.contains(currentBoardState)) continue;

        visitedBoardStates.insert(currentBoardState);

        int cellOfEmptySpace = getCellOfEmptySpace(currentBoardState);
        int rowOfEmptySpace = getRowOfCell(cellOfEmptySpace);
        int colOfEmptySpace = getColOfCell(cellOfEmptySpace);

        std::vector<int> nextBoardState = currentBoardState;
        int cellOfEmptySpaceCopy = cellOfEmptySpace;

        std::shared_ptr<Node> parent = std::make_shared<Node>(currentNode);

        if (rowOfEmptySpace < n - 1) {
            applyMove(nextBoardState, cellOfEmptySpace, 'U');
            queue.emplace(nextBoardState, parent, 'U');

            nextBoardState = currentBoardState;
            cellOfEmptySpace = cellOfEmptySpaceCopy;
        }
        if (rowOfEmptySpace > 0) {
            applyMove(nextBoardState, cellOfEmptySpace, 'D');
            queue.emplace(nextBoardState, parent, 'D');

            nextBoardState = currentBoardState;
            cellOfEmptySpace = cellOfEmptySpaceCopy;
        }

        if (colOfEmptySpace == 0) {
            applyMove(nextBoardState, cellOfEmptySpace, 'L');
            queue.emplace(nextBoardState, parent, 'L');
        }
        else {
            applyMove(nextBoardState, cellOfEmptySpace, 'R');
            queue.emplace(nextBoardState, parent, 'R');
        }
    }

    boardState = currentNode.boardState;

    std::string optimalMoveSequence;
    std::shared_ptr<Node> currentNodePointer = std::make_shared<Node>(currentNode);

    while (currentNodePointer->parent) {
        optimalMoveSequence = currentNodePointer->direction + optimalMoveSequence;
        currentNodePointer = currentNodePointer->parent;
    }

    return optimalMoveSequence;
}
