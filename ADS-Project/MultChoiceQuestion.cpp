#include <iostream>
#include "QuizQuestion.h"
#include "MultChoiceQuestion.h"
#include "QuizManager.h"
#include <string>

using namespace std;

//constructor implementation
MultChoiceQuestion::MultChoiceQuestion(string newQuestion, string choices[4], int index, int points) {
	QuizQuestion::question = newQuestion;

	for (int i = 0; i < choices->size(); i++) {
		choiceArr[i] = choices[i];
	}

	answerIndex = index;
	QuizQuestion::pointValue = points;
}

MultChoiceQuestion::MultChoiceQuestion(string newQuestion, string choice1, string choice2, string choice3, string choice4, int index, int points)
{
	QuizQuestion::question = newQuestion;
	choiceArr[0] = choice1;
	choiceArr[1] = choice2;
	choiceArr[2] = choice3;
	choiceArr[3] = choice4;
	answerIndex = index;
	QuizQuestion::pointValue = points;
}
//function implementation

bool MultChoiceQuestion::Evaluate(int index) {
	if (index == answerIndex) {
		cout << "Correct answer!" << endl;
		QuizManager::playerScore += pointValue; //adding the points to the score
		cout <<  "current score: " << QuizManager::playerScore << endl;
		return true;	
	}
	else
	{
		cout << "Wrong answer!" << endl;
		return false;
	}
}

void MultChoiceQuestion::DisplayQuestion() {

	string TempanswerIndex;

	cout << "Multiple Choice Question" << endl;


	cout << question << endl;

	for (int i = 0; i < 4; i++) {

		cout << (i + 1) << ". " << choiceArr[i] << endl;
	}

	cout << "Please chose one of the options" << endl;

	cin >> TempanswerIndex;

	try
	{
		int answerIndex = std::stoi(TempanswerIndex);
		if (answerIndex >= 1 && answerIndex <= 4)
		{
			Evaluate(answerIndex - 1); // -1 because the array starts from 0
		}
		else
		{
			std::cout << "Please choose a valid option" << std::endl;
			system("cls"); //clean the screen			
		}
	}
	catch (const std::exception&)
	{
		system("cls"); //clean the screen
		DisplayQuestion();
	}
}
