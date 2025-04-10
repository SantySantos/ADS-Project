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

	list<string> quizFileNames; // list to get the .cvs files names in the folder, and open them eventually.

	//functions

	void DisplayOptions();

	void OptionChosen(int option);

	std::list<std::string> GetQuizFilesNames(); // Fixed: Use std::list and std::string  

	Quiz Load(const std::string& filePath);

	Quiz Create();

};