#include <iostream>
#include <string>
#include "QuizManager.h"
#include <filesystem>
#include "MultChoiceQuestion.h"
#include "TrueFalseQuestion.h"
#include <fstream>
#include "Quiz.h"

using namespace std;
namespace fs = std::filesystem;

int QuizManager::playerScore = 0;
Quiz QuizManager::quizToPlay;

//constructor implementation
QuizManager::QuizManager() : FilesFolder(fs::current_path()), directoryQuestions(FilesFolder / "Quizes") {


	DisplayOptions();
}

//functions implementations

vector<string> QuizManager::GetQuizFilesNames() {

	int currentIndex = 0;
	//looping thorught the contains of the file and getting the names of them
	for (auto entry : fs::directory_iterator(directoryQuestions)) //auto is like var in c#, letting the complier figure out the type
	{
		quizFileNames.push_back(entry.path().filename().string()); //saving the file name in the list
	}

	return quizFileNames;
}

Quiz QuizManager::Create() {
	int questionNum;
	Quiz quiz;
	cout << "CREATE MUST BE IMPLEMENTED" << endl;
	cout << "How many questions would you like to add?" << endl;
	cin >> questionNum;
	for (int i = 0; i < questionNum;) {
		string question;
		string choices[4];
		int answerIndex;
		int points;
		cout << "Type question " << i << ": " << endl;
		getline(cin, question);
		for (int j = 0; j < 4; j++) {
			cout << "Type choice " << j << ": " << endl;
		}
		cout << "Which choice is the correct one?" << endl;
		cin >> answerIndex;
		cout << "How many points is this question worth?";
		cin >> points;
	}

	return quiz;
}

Quiz QuizManager::Load() { // static 

	GetQuizFilesNames(); //getting the quiz file names

	//attributes
	int currentIndex = 0;

	//Load the quiz from the file path
	Quiz Chosenquiz;

	string userInput = ""; //variable to store the user input
	int userOption = 0;

	if (fs::exists(directoryQuestions)) //checking if the dir exits, if not, create it
	{
		// PARSE THE FILE LINE BY LINE, FOR EACH LINE SPLIT USING THE DELIMITER "," AND STORE THE VALUES IN A QUIZ OBJECT

		for (std::string myFile : quizFileNames)
		{
			++currentIndex; //pre-incrementing the index
			cout << currentIndex << ". "; //printing the index of the file
			cout << myFile << endl; //printing the file names
		}
		cout << endl;

		cout << "Please choose one of the options:" << endl;

		cin.ignore();
		std::getline(cin, userInput); // Corrected the order of arguments for getline

		//getting user input until it does not fail anymore and inserts a valid value
		while (true)
		{
			try
			{
				userOption = std::stoi(userInput); //converting the string to int

				if (userOption > 0 && userOption <= quizFileNames.size())
				{
					//open the file
					std::string chosenFile = quizFileNames[userOption - 1]; //getting the quiz chosen name from the vector.

					std::ifstream file(directoryQuestions / chosenFile); //opening the file

					Chosenquiz.quizName = chosenFile; //setting the quiz name


					while (file.peek() != EOF)
					{

						Chosenquiz.myQuestions.push_back(QuizQuestion(InsertingToQuiz(file))); //inserting the question to the quiz

					}

					file.close(); //closing the file

					return Chosenquiz; //returning the quiz object

				}
				else {
					cout << "Please choose a valid option" << endl;
				}
			}
			catch (std::exception)
			{
				cout << "Please enter a number" << endl;
			}

			cin.ignore();
			std::getline(cin, userInput);
		}
	}
	else {

		fs::create_directory(directoryQuestions);
		Load(); //recursive call to load the quiz after its created 
	}

	currentIndex = 0; //resetting the index 

	return Chosenquiz;
}

QuizQuestion QuizManager::InsertingToQuiz(ifstream& file)
{
	try
	{
		//tempHolders
		std::string tempQuizType = "";
		std::string tempQuestion = "";
		std::string answers[4];
		std::string tempCorrectIndex = "";
		int tempIndex = 0;
		std::string StempScore = "";
		int tempScore = 0;

		getline(file, tempQuizType, ','); //reading the first line of the file

		if (tempQuizType == "M") //checking if the question type is MULTCHOICE
		{
			std::getline(file, tempQuestion, ',');
			std::getline(file, answers[0], ',');
			std::getline(file, answers[1], ',');
			std::getline(file, answers[2], ',');
			std::getline(file, answers[3], ',');
			std::getline(file, tempCorrectIndex, ',');
			tempIndex = std::stoi(tempCorrectIndex); //converting the string to int
			std::getline(file, StempScore, '\n');
			tempScore = std::stoi(StempScore);
			MultChoiceQuestion tempQuizQuestion(tempQuestion, answers, tempIndex, tempScore);
			return tempQuizQuestion;
		}
		else if (tempQuizType == "B") //checking if the question type is true or false 
		{

			std::getline(file, tempQuestion, ',');
			std::getline(file, tempCorrectIndex, ',');
			tempIndex = std::stoi(tempCorrectIndex); //converting the string to int
			std::getline(file, StempScore, '\n');
			tempScore = std::stoi(StempScore);
			TrueFalseQuestion tempQuizQuestion(tempQuestion, tempIndex, tempScore);
			return tempQuizQuestion; //returning the question object
		}
		else
		{
			throw  "Please enter a valid question type";

		}


	}
	catch (const std::exception&)
	{
		cout << "Sorry, we have a problem..." << endl;
	}

}
void QuizManager::OptionChosen(int currentOption) {

	cin >> currentOption;

	switch (currentOption)
	{
	case 1:
		QuizManager::quizToPlay = Load();
		system("cls"); //clean the screen
		quizToPlay.Evaluate();
		break;
	case 2:
		Create();
		break;
	case 3:
		cout << "You choose third option.\n";
		break;
	case 4:
		cout << "You choose fourth option.\n";
		break;
	default:
		cin.clear();
		cin.ignore(4096, '\n');
		//we ignore the following 4096 characters in the line as that is the max amount there can be in any compiler
		cout << "Please choose a valid option\n";
		OptionChosen(currentOption);
		break;
	}
}
void QuizManager::DisplayOptions()
{
	int currentOption = 0;

	cout << "WELCOME TO (INSERT APP NAME HERE) \n";

	cout << "Please choose an option from the following ones and press enter\n"
		"1. Answer a quiz \n"
		"2. Create a quiz \n"
		"3. Information \n"
		"4. Exit the application \n";
	OptionChosen(currentOption);
}