
#ifndef API_H
#define API_H
#include "json.hpp"
#include <vector>
using json = nlohmann::json;

// Starts hosting the server on localhost:8080.
void runAPI();

// Encodes the given board state into a json.
json boardStateToJson(const std::vector<int>& boardState);
// Returns the board state encoded into the given json.
std::vector<int> jsonToBoardState(const json& j);
// Reads the given file.
std::string readFile(const std::string& fileName);

#endif //API_H
