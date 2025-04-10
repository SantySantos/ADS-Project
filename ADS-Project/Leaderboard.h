#pragma once

#include <iostream>
#include <map>
#include <string>

using namespace std;

class Leaderboard {

public:

	std::map<int, std::map<std::string ,int >> board;

	void Load();

	void Save();

};