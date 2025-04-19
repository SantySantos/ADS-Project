#pragma once

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

class Leaderboard {

public:

	map<int, map<string, int>> leaderboard;

	void Load(string& filename);

	void Save(string& filename);

	void UpdateScore(int quizID, const string& username, int score);

private:
	const int BOARD_MAX = 5;
};