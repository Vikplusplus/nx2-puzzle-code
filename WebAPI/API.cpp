
#include "API.h"
#include "../Algorithms/general.h"
#include "../Algorithms/optimalSolution.h"

#include "../Algorithms/numbered/generateBoardState.h"
#include "../Algorithms/numbered/rowByRow.h"
#include "../Algorithms/numbered/divideOnce.h"

#include "../Algorithms/twoColor/generateBoardState.h"
#include "../Algorithms/twoColor/rowByRow.h"
#include "../Algorithms/twoColor/partitionOnce.h"

#include "../Algorithms/kColor/generateBoardState.h"
#include "../Algorithms/kColor/rowByRow.h"
#include "../Algorithms/kColor/colorByColor.h"

#include "httplib.h"
#include <fstream>

#include "../Algorithms/numbered/divideAndConquer.h"

void runAPI() {
    httplib::Server server;

    server.Get("/", [](const httplib::Request&, httplib::Response& res) {
        res.set_content(readFile("WebAPI/index.html"), "text/html");
    });
    server.Get("/styles.css", [](const httplib::Request&, httplib::Response& res) {
        res.set_content(readFile("WebAPI/styles.css"), "text/css");
    });
    server.Get("/script.js", [](const httplib::Request&, httplib::Response& res) {
        res.set_content(readFile("WebAPI/script.js"), "application/javascript");
    });


    server.Get("/generateInitialBoardState_numbered", [](const httplib::Request&, httplib::Response& res) {
        std::vector<int> initialBoardState = num::generateSolvableBoardState(5);
        json j = boardStateToJson(initialBoardState);
        res.set_content(j.dump(), "application/json");
    });
    server.Get("/generateInitialBoardState_twoColor", [](const httplib::Request&, httplib::Response& res) {
        std::vector<int> initialBoardState = twoClr::generateBoardState_binomial(5, 0.5);
        json j = boardStateToJson(initialBoardState);
        res.set_content(j.dump(), "application/json");
    });
    server.Get("/generateInitialBoardState_kColor", [](const httplib::Request&, httplib::Response& res) {
        std::vector<int> initialBoardState = kClr::generateBoardState(5,4);
        json j = boardStateToJson(initialBoardState);
        res.set_content(j.dump(), "application/json");
    });


    server.Post("/move", [](const httplib::Request& req, httplib::Response& res) {
        auto body = json::parse(req.body);

        std::vector<int> boardState = jsonToBoardState(body);
        int cellOfEmptySpace = getCellOfEmptySpace(boardState);

        char direction = body["direction"].get<std::string>()[0];

        if (isMoveValid(boardState, cellOfEmptySpace, direction)) {
            applyMove(boardState, cellOfEmptySpace, direction);
            json response = boardStateToJson(boardState);
            res.set_content(response.dump(), "application/json");
        } else {
            res.status = 400;
            res.set_content("Invalid move", "text/plain");
        }
    });


    server.Post("/generateState_numbered", [](const httplib::Request& req, httplib::Response& res) {
        auto body = json::parse(req.body);

        int n = body["n"].get<int>();
        std::vector<int> boardState = num::generateSolvableBoardState(n);

        json response = boardStateToJson(boardState);
        res.set_content(response.dump(), "application/json");
    });
    server.Post("/generateState_twoColor", [](const httplib::Request& req, httplib::Response& res) {
        auto body = json::parse(req.body);

        int n = body["n"].get<int>();
        std::vector<int> boardState = twoClr::generateBoardState_binomial(n, 0.5);

        json response = boardStateToJson(boardState);
        res.set_content(response.dump(), "application/json");
    });
    server.Post("/generateState_kColor", [](const httplib::Request& req, httplib::Response& res) {
        auto body = json::parse(req.body);

        int n = body["n"].get<int>();
        int k = body["k"].get<int>();
        std::vector<int> boardState = kClr::generateBoardState(n, k);

        json response = boardStateToJson(boardState);
        res.set_content(response.dump(), "application/json");
    });


    server.Post("/optimalSolution", [](const httplib::Request& req, httplib::Response& res) {
        auto body = json::parse(req.body);

        std::vector<int> boardState = jsonToBoardState(body);

        std::string moveSequence = optimalSolution(boardState);

        json response = { {"moveSequence", moveSequence} };
        res.set_content(response.dump(), "application/json");
    });


    server.Post("/RowByRow_numbered", [](const httplib::Request& req, httplib::Response& res) {
        auto body = json::parse(req.body);

        std::vector<int> boardState = jsonToBoardState(body);

        std::string moveSequence = num::rowByRow(boardState);

        json response = { {"moveSequence", moveSequence} };
        res.set_content(response.dump(), "application/json");
    });

    server.Post("/DivideOnce_numbered", [](const httplib::Request& req, httplib::Response& res) {
        auto body = json::parse(req.body);

        std::vector<int> boardState = jsonToBoardState(body);

        std::string moveSequence = num::divideOnce(boardState);

        json response = { {"moveSequence", moveSequence} };
        res.set_content(response.dump(), "application/json");
    });

    server.Post("/DivideAndConquer_numbered", [](const httplib::Request& req, httplib::Response& res) {
        auto body = json::parse(req.body);

        std::vector<int> boardState = jsonToBoardState(body);

        std::string moveSequence = num::divideAndConquer(boardState);

        json response = { {"moveSequence", moveSequence} };
        res.set_content(response.dump(), "application/json");
    });



    server.Post("/RowByRow_twoColor", [](const httplib::Request& req, httplib::Response& res) {
        auto body = json::parse(req.body);

        std::vector<int> boardState = jsonToBoardState(body);

        std::string moveSequence = twoClr::rowByRow(boardState);

        json response = { {"moveSequence", moveSequence} };
        res.set_content(response.dump(), "application/json");
    });

    server.Post("/PartitionOnce_twoColor", [](const httplib::Request& req, httplib::Response& res) {
        auto body = json::parse(req.body);

        std::vector<int> boardState = jsonToBoardState(body);

        std::string moveSequence = twoClr::partitionOnce(boardState);

        json response = { {"moveSequence", moveSequence} };
        res.set_content(response.dump(), "application/json");
    });



    server.Post("/RowByRow_kColor", [](const httplib::Request& req, httplib::Response& res) {
        auto body = json::parse(req.body);

        std::vector<int> boardState = jsonToBoardState(body);

        std::string moveSequence = kClr::rowByRow(boardState);

        json response = { {"moveSequence", moveSequence} };
        res.set_content(response.dump(), "application/json");
    });

    server.Post("/ColorByColor_kColor", [](const httplib::Request& req, httplib::Response& res) {
        auto body = json::parse(req.body);

        std::vector<int> boardState = jsonToBoardState(body);

        std::string moveSequence = kClr::colorByColor(boardState);

        json response = { {"moveSequence", moveSequence} };
        res.set_content(response.dump(), "application/json");
    });


    std::cout << "Server running at http://localhost:8080\n";
    server.listen("localhost", 8080);
}

json boardStateToJson(const std::vector<int> &boardState) {
    json j;
    for (int cell : boardState) j["boardState"].push_back(cell);
    return j;
}

std::vector<int> jsonToBoardState(const json &j) {
    if (j.contains("boardState") && j["boardState"].is_array()) {
        return j["boardState"].get<std::vector<int>>();
    }
    return {};
}

std::string readFile(const std::string &fileName) {
    std::ifstream file(fileName);
    if (!file) {
        std::cerr << "Failed to open file: " << fileName << std::endl;
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

