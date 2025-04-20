#include <iostream>
#include <string>
#include "QuizManager.h"
#include <filesystem>
#include "MultChoiceQuestion.h"
#include "TrueFalseQuestion.h"
#include <fstream>
#include <list>
#include "Quiz.h"


namespace fs = std::filesystem;

int QuizManager::playerScore = 0;
Quiz QuizManager::quizToPlay;
std::string QuizManager::Username = ""; 

using namespace std;
//constructor implementation
QuizManager::QuizManager() : FilesFolder(fs::current_path()), directoryQuestions(FilesFolder / "Quizes") {


	DisplayOptions();
}

//getter and setter implementation
std::string QuizManager::GetUsername() {
	return Username;
}
void QuizManager::SetUsername() {

	cin.clear();
	cin.ignore();
	
	std::string value; //variable to store the username

	cout << "\n" << "please enter your username for the leaderboard" << endl;

	std::getline(cin, value); //getting the username from the user

	if (value.empty()) //checking if the username is empty
	{
		cout << "Please enter a valid username" << endl;
		SetUsername(); //recursive call to set the username
	}
	else
	{
		Username = value; //setting the username
	}
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
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "How many points is this question worth?" << endl;
            cin >> points;
			quiz.myQuestions->push_back(new MultChoiceQuestion(question, choices[0], choices[1], choices[2], choices[3], answerIndex, points));
            
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
            file << mcq->getQuestion() + ",";
            for (int i = 0; i < 4; i++) {
                file << mcq->choiceArr[i];
                if (i != 3) {
                    file << ",";
                }
            }
            file << ",";
            file << to_string(mcq->answerIndex) + ",";
            file << mcq->getPoints();
        }

        else if (typeid(*q) == typeid(TrueFalseQuestion)) {
            TrueFalseQuestion* tfq = dynamic_cast<TrueFalseQuestion*>(q);
            file << "True or False, ";
            file << tfq->getQuestion() + ",";
            file << ",,,,";
            file << (tfq->getAnswer() ? "True" : "False") << ",";
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
					std::string discardline = ""; //variable to discard the first line of the file
					Chosenquiz.quizName = chosenFile; //setting the quiz name

					std::getline(file, discardline, '\n');
					cout << "discated line = " << discardline << endl;

					while (file.peek() != EOF)
					{
						QuizQuestion* tempQuestion = InsertingToQuiz(file); //creating a question object
						if (tempQuestion != nullptr) //checking if the question is null
						{
							cout << "Address of temp quiz:" << tempQuestion <<endl;
							Chosenquiz.myQuestions->push_back(tempQuestion); //adding the question to the quiz
									
						}
						else
						{
							cout << "Error while creating the question" << endl;
						}
					
					}
					for (QuizQuestion* q : *(Chosenquiz.myQuestions)) {
						cout << "Address in list: " << q << endl;
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
				cin.clear();
				cin.ignore(4096, '\n'); //we ignore the following 4096 characters in the line as that is the max amount there can be in any compiler
				continue; //continue the loop
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


QuizQuestion* QuizManager::InsertingToQuiz(ifstream& file)
{
	try
	{
		//tempHolders
		std::string tempLine = ""; //variable to store the line
		std::string tempQuizType = "";
		std::string tempQuestion = "";
		std::string answers[4];
		std::string tempCorrectIndex = "";
		int tempIndex = 0;
		std::string StempScore = "";
		int tempScore = 0;

		getline(file, tempQuizType, ','); //reading the first line of the file

		if (tempQuizType == "Multiple Choice") //checking if the question type is MULTCHOICE
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
			MultChoiceQuestion *tempQuizQuestion =  new MultChoiceQuestion(tempQuestion, answers[0],answers[1], answers[2], answers[3], tempIndex, tempScore);
			/*
			for (int i = 0; i < 4; i++)
			{
				tempQuizQuestion->choiceArr[i] = answers[i]; //setting the answers in the array
				cout << tempQuizQuestion->choiceArr[i] << endl;
			}
			*/
			
			return tempQuizQuestion;
		}
		else if (tempQuizType == "True or False") //checking if the question type is true or false 
		{

			std::getline(file, tempQuestion, ',');
			for (int i = 0; i < 4; i++) {
				std::getline(file, tempLine, ','); //ignoring the next 4 lines
			}
			std::getline(file, tempCorrectIndex, ',');
			if (tempCorrectIndex == "True") //checking if the answer is true
			{
				tempCorrectIndex = "1"; //setting the correct index to 1
			}
			else if (tempCorrectIndex == "False") //checking if the answer is false
			{
				tempCorrectIndex = "0"; //setting the correct index to 0
			}
			tempIndex = std::stoi(tempCorrectIndex); //converting the string to int
			std::getline(file, StempScore, '\n');
			tempScore = std::stoi(StempScore);
			TrueFalseQuestion *tempQuizQuestion = new TrueFalseQuestion(tempQuestion, tempIndex, tempScore);
			return tempQuizQuestion; //returning the question object
		}
		
			
		
	}
	catch (const std::exception&)
	{
		cout << "Sorry, we have a problem..." << endl;
		return nullptr;
	}

}

void QuizManager::Information() {
	cout << "This is a quiz application that allows you to create and play quizzes." << endl;
	cout << "You can choose from a variety of quizzes or create your own." << endl;
	cout << "You can choose to play a quiz and test your knowledge." << endl;
	cout << "You can also create your own quiz and share it with others." << endl;
	cout << "Please have into account that at the moment you are creating quizes, dont add any commas for anything, as it can CRASH the program" << endl;
	cout << "Have fun!" << endl;

	cout << "Press any key to go back to the main menu" << endl;
	cin.clear();
	cin.ignore(4096, '\n'); //we ignore the following 4096 characters in the line as that is the max amount there can be in any compiler
	cin.get(); //wait for the user to press any key
	system("cls"); //clean the screen
	DisplayOptions(); //display the options again

}
void QuizManager::OptionChosen(int currentOption) {

	cin >> currentOption;

	switch (currentOption)
	{
	case 1:
		QuizManager::quizToPlay = Load();
		system("cls"); //clean the screen
		quizToPlay.Evaluate();
		cout << "Final Score: " << QuizManager::playerScore; //resetting the score
		QuizManager::SetUsername(); //setting the username
		break;
	case 2:
		Create();
		break;
	case 3:QuizManager::Information();
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

	cout << "WELCOME TO YOUR QUIZ LOBBY \n";

	cout << "Please choose an option from the following ones and press enter\n"
		"1. Answer a quiz \n"
		"2. Create a quiz \n"
		"3. Information \n"
		"4. Exit the application \n";
	OptionChosen(currentOption);
}