#pragma once

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>


class Leaderboard {
public:
    void Load(const std::string& filename);
    void Save(const std::string& filename);
    void UpdateScore(int quizID, const std::string& username, int score);
    void Print()const;


private:
    std::map<int, std::map<std::string, int>> leaderboard;
    static const int BOARD_MAX = 5;
};
