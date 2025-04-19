#include "Leaderboard.h"
#include "iostream"


using namespace std;

void Leaderboard::Load(string& filename) {

	//to clear existing data in the leaderboard
	leaderboard.clear();

	//open the file
	ifstream MyFile(filename);
	string line, username;
	int quizID, score;

	//read each line from the file
	while (getline(MyFile, line)) {
		stringstream ss(line);
		ss >> quizID; //read the quiz ID

		//read and store the username and the score from each line
		map<string, int> scores;
		while (ss >> username >> score) {
			scores[username] = score;
		}

		leaderboard[quizID] = scores; //store the leaderBoard
	}

	MyFile.close();
}
void Leaderboard::Save(string& filename) {
	//open the file
	ofstream Myfile(filename);

	//iterate over each quz=iz entry
	for (const auto& quizEntry : leaderboard) {
		int quizID = quizEntry.first;
		Myfile << quizID; //write the quizID first

		//convert the score map to vector for sorting
		vector<pair<string, int>> sorted(quizEntry.second.begin(), quizEntry.second.end());

		//sort by descending order
		sort(sorted.begin(), sorted.end(), [](const auto& a, const auto& b) {
			return a.second > b.second
			});

		//write the top score to file
		int count = 0;
		for (const auto& entry : sorted) {
			if (count++ >= BOARD_MAX)
				break;

			Myfile << " " << entry.first << " " << entry.second;
			Myfile << endl;
		}
	}

	Myfile.close();
}

void Leaderboard::UpdateScore(int quizID, const string& username, int score) {
	auto& board = leaderboard[quizID]; // get the score map for that quiz

	// update only if the new score is higher
	if (board.find(username) != board.end()) {
		if (score > board[username]) {
			board[username] = score;
		}
	}
	else {
		board[username] = score;
	}

	// trim to top BOARD_MAX entries
	vector<pair<string, int>> sorted(board.begin(), board.end());

	sort(sorted.begin(), sorted.end(), [](const auto& a, const auto& b) {
		return a.second > b.second;
		});

	if (sorted.size() > BOARD_MAX) {
		board.clear();
		for (int i = 0; i < BOARD_MAX; ++i) {
			board[sorted[i].first] = sorted[i].second;
		}
	}
}

