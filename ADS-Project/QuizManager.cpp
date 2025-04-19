#include <iostream>
#include <string>
#include "QuizManager.h"
#include <filesystem>
#include "MultChoiceQuestion.h"
#include "TrueFalseQuestion.h"
#include <fstream>
#include <list>
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
    cout << "How many questions would you like to add?" << endl;
    cin >> questionNum;
    cout << questionNum << endl;
    for (int i = 0; i < questionNum; i++) {
        int type;
        string question;
        string choices[4];
        int answerIndex;
        int points;
        while (true) {
            cout << "What type of question will it be? \n 1. Multiple Choice \n 2. True or False" << endl;
            cin >> type;
            if (cin.fail() || type != 1 && type != 2) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Please choose a valid number." << endl;
            }
            else {
                break;
            }
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter the question " << i + 1 << ": " << endl;
        getline(cin, question);
        if (type == 1) {
            for (int j = 0; j < 4; j++) {
                cout << "Type choice " << j + 1 << ": " << endl;
                getline(cin,choices[j]);
            }
            cout << "Which choice is the correct one?" << endl;
            cin >> answerIndex;
            answerIndex--;
            cout << "How many points is this question worth?" << endl;
            cin >> points;
            quiz.myQuestions->push_back(new MultChoiceQuestion(question, choices, answerIndex, points));
        }
        else if(type == 2) {
            bool answer;
            cout << "Is this answer \n 1. True \n 2. False" << endl;
            cin >> answerIndex;
            if (answerIndex == 1) {
                answer = true;
            }
            else if (answerIndex == 2) {
                answer = false;
            }
            cout << "How many points is this question worth?" << endl;
            cin >> points;
            quiz.myQuestions->push_back(new TrueFalseQuestion(question, answer, points));
        }
        else {
            cout << "Invalid input." << endl;
        }
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string filename;
    cout << "What is the name of this file?" << endl;
    getline(cin, filename);
    ofstream file("Quizes/" + filename + ".csv");
    file << "Type,Question,Option1,Option2,Option3,Option4,Answer,Points\n";
    int qSize = quiz.myQuestions->size();
    for (QuizQuestion* q : *(quiz.myQuestions)) {
        if (typeid(*q) == typeid(MultChoiceQuestion)) {
            MultChoiceQuestion* mcq = dynamic_cast<MultChoiceQuestion*>(q);
            file << "Multiple Choice, ";
            file << mcq->getQuestion() + ", ";
            for (int i = 0; i < 4; i++) {
                file << mcq->choiceArr[i] + ", ";
            }
            file << mcq->answerIndex + ", ";
            file << mcq->getPoints();
        }

        else if (typeid(*q) == typeid(TrueFalseQuestion)) {
            TrueFalseQuestion* tfq = dynamic_cast<TrueFalseQuestion*>(q);
            file << "True or False, ";
            file << tfq->getQuestion() + ", ";
            file << ",,,, ";
            file << (tfq->getAnswer() ? "True" : "False") << ", ";
            file << tfq->getPoints();
        }
        file << "\n";
    }
    file.close();
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

				Chosenquiz.myQuestions->push_back(new QuizQuestion(InsertingToQuiz(file))); //creating a question object and adding it to the quiz
                        
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
		std::string discardline = "";	
		std::string tempQuizType = "";
		std::string tempQuestion = "";
		std::string answers[4];
		std::string tempCorrectIndex = "";
		int tempIndex = 0;
		std::string StempScore = "";
		int tempScore = 0;

		getline(file, tempQuizType, ','); //reading the first line of the file

		if (tempQuizType == "MultChoiceQuestion") //checking if the question type is MULTCHOICE
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
		else if (tempQuizType == "TrueFalseQuestion") //checking if the question type is true or false 
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
			std::getline(file, discardline, '\n');
			discardline = ""; //clearing the line
			InsertingToQuiz(file); //recursive call to load the quiz after its created
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