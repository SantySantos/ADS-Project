#pragma once

#include <string>  
#include "Quiz.h"  
#include <filesystem>  
#include <iostream>  
#include <list> 

namespace fs = std::filesystem;

class QuizManager {
public:
	//constructor
	QuizManager();

	//attributes
	fs::path FilesFolder = fs::current_path();

	const fs::path directoryQuestions = FilesFolder / "Quizes"; // Constant QUIZ_FOLDER 

	vector<string> quizFileNames; // list to get the .cvs files names in the folder, and open them eventually.

	//functions 

	void DisplayOptions();

	void OptionChosen(int option);

	vector<std::string> GetQuizFilesNames(); // Fixed: Use std::vector and std::string  

	Quiz Load();

	Quiz Create(); // needs to be implemented

};