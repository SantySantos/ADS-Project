#include "Leaderboard.h"
#include <windows.h>
#include "iostream"


using namespace std;

void SetColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void Leaderboard::Load(const std::string& filename) {
    leaderboard.clear();
    std::ifstream MyFile(filename);
    if (!MyFile.is_open()) {
        std::cerr << "Could not open file: " << filename << std::endl;
        return;
    }

    std::string line, username;
    int quizID, score;

    while (std::getline(MyFile, line)) {
        std::stringstream ss(line);
        ss >> quizID;

        std::map<std::string, int> scores;
        while (ss >> username >> score) {
            scores[username] = score;
        }

        leaderboard[quizID] = scores;
    }

    MyFile.close();
}

void Leaderboard::Save(const std::string& filename) {
    std::ofstream MyFile(filename);
    if (!MyFile.is_open()) {
        std::cerr << "Could not open file: " << filename << std::endl;
        return;
    }

    for (const auto& quizEntry : leaderboard) {
        int quizID = quizEntry.first;
        MyFile << quizID;

        // Sort entries
        std::vector<std::pair<std::string, int>> sorted(quizEntry.second.begin(), quizEntry.second.end());
        std::sort(sorted.begin(), sorted.end(), [](const auto& a, const auto& b) {
            return a.second > b.second;
            });

        int count = 0;
        for (const auto& entry : sorted) {
            if (count++ >= BOARD_MAX)
                break;
            MyFile << " " << entry.first << " " << entry.second << "\n";
        }
        MyFile << std::endl;
    }

    MyFile.close();
}

void Leaderboard::UpdateScore(int quizID, const std::string& username, int score) {
    auto& board = leaderboard[quizID];

    // Only update if score is higher
    if (board.find(username) != board.end()) {
        if (score > board[username]) {
            board[username] = score;

        }
    }
    else {
        board[username] = score;
    }

    // Trim to BOARD_MAX entries
    std::vector<std::pair<std::string, int>> sorted(board.begin(), board.end());
    std::sort(sorted.begin(), sorted.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
        });

    if (sorted.size() > BOARD_MAX) {
        board.clear();
        for (int i = 0; i < BOARD_MAX; ++i) {
            board[sorted[i].first] = sorted[i].second;
        }
    }
}

void Leaderboard::Print(const std::string& filename) {

   leaderboard.clear();
    std::ifstream MyFile(filename);
    if (!MyFile.is_open()) {
        std::cerr << "Could not open file: " << filename << std::endl;
        return;
    }

    std::string line, username;
    int quizID, score;

    while (std::getline(MyFile, line)) {
        std::stringstream ss(line);
        ss >> quizID;

        auto& scores = leaderboard[quizID];

        while (ss >> username >> score) {
            scores[username] = score;
        }

        leaderboard[quizID] = scores;
    }

    MyFile.close();

    for (const auto& quizEntry : leaderboard) {
        int quizID = quizEntry.first;
        SetColor(9);
        std::cout << "---------------------------\n";
        std::cout << "Username      | Score\n";
        std::cout << "---------------------------\n";
        SetColor(7);

        std::vector<std::pair<std::string, int>> sorted(quizEntry.second.begin(), quizEntry.second.end());
        std::sort(sorted.begin(), sorted.end(), [](const auto& a, const auto& b) {
            return a.second > b.second;
            });

        int count = 0;
        for (const auto& entry : sorted) {
            if (count++ >= BOARD_MAX) break;
            SetColor(6);
            std::cout << entry.first << std::string(14 - entry.first.size(), ' ');
            SetColor(9);
            std::cout << "| ";
            SetColor(8);
            std::cout << entry.second << "\n";
        }
        SetColor(7);
        std::cout << "\n";
    }
}

