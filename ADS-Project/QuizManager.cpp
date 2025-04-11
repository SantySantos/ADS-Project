#include <iostream>
#include <string>
#include "QuizManager.h"
#include <filesystem>
#include <fstream>

using namespace std;
namespace fs = std::filesystem;

//constructor implementation
QuizManager::QuizManager(): FilesFolder(fs::current_path()), directoryQuestions(FilesFolder / "Quizes") {
	
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
	cout << "CREATE MUST BE IMPLEMENTED" << endl;
	return Quiz();
}

Quiz QuizManager::Load() { // static 

    GetQuizFilesNames(); //getting the quiz file names

    //attributes
    int currentIndex = 0;

    //Load the quiz from the file path
    Quiz Chosenquiz;

    string userInput = ""; //variable to store the user input
    int userOption = 0;

    if (fs::exists(directoryQuestions)) //checking if the golder exits, if not, create it
    {
        // PARSE THE FILE LINE BY LINE, FOR EACH LINE SPLIT USING THE DELIMITER "," AND STORE THE VALUES IN A QUIZ OBJECT
        // CREATE the question and addd it to quiz
        cout << "Please choose one of the options below to start answering your quiz" << endl;

        for (std::string myFile : quizFileNames)
        {
            ++currentIndex; //pre-incrementing the index
            cout << currentIndex << ". "; //printing the index of the file
            cout << myFile << endl; //printing the file names
        }
        cout << "";

        cout << "Please choose one of the options:" << endl;

        cin.ignore();
        getline(cin, userInput); // Corrected the order of arguments for getline

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

                    for (std::string line; getline(file, line);) {  //reading the file line by line
                    
                        

                    }
                    
                }
                else
                {
                    cout << "Please choose a valid option" << endl;
                }
            }
            catch (std::exception)
            {
                cout << "Please enter a number" << endl;
            }

            cin.ignore();
            getline(cin, userInput);

        }
    }
    else {

        fs::create_directory(directoryQuestions);
        Load(); //recursive call to load the quiz after its created 
    }

    currentIndex = 0; //resetting the index 
    return Chosenquiz;
}
void QuizManager::OptionChosen(int currentOption) {

    cin >> currentOption;

    switch (currentOption)
    {
    case 1:
        Load();
        //Play();
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