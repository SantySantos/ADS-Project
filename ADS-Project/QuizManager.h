#pragma once

#include <string>  
#include "Quiz.h"  
#include <filesystem>  
#include <iostream>  
#include <list> 
#include "MultChoiceQuestion.h"
#include "TrueFalseQuestion.h"

namespace fs = std::filesystem;

class QuizManager {
public:
	//constructor
	QuizManager();

	static int playerScore;  //static variable to keep the score of the player

	static Quiz quizToPlay;

	//attributes
	fs::path FilesFolder = fs::current_path();

	const fs::path directoryQuestions = FilesFolder / "Quizes"; // Constant QUIZ_FOLDER 

	vector<string> quizFileNames; // list to get the .cvs files names in the folder, and open them eventually.

	//functions 

	void DisplayOptions();

	void OptionChosen(int option);

	QuizQuestion InsertingToQuiz(std::ifstream& file);


	vector<std::string> GetQuizFilesNames(); // Fixed: Use std::vector and std::string  

	Quiz Load();

	Quiz Create(); // needs to be implemented

};