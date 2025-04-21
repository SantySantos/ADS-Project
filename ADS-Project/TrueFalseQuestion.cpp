#include <iostream>
#include "QuizQuestion.h"
#include "TrueFalseQuestion.h"
#include <string>
#include "QuizManager.h"

bool TrueFalseQuestion::getAnswer()
{
	return correctAnswer;
}

//constructor implementation
TrueFalseQuestion::TrueFalseQuestion(string newQuestion, bool answer, int points) {
	QuizQuestion::question = newQuestion;
	correctAnswer = answer;
	QuizQuestion::pointValue = points;
}

bool TrueFalseQuestion::Evaluate(bool answer) {

	if (answer == correctAnswer)
	{
		cout << "Correct answer!" << endl;
		QuizManager::playerScore += pointValue; //adding the points to the score
		cout << "current score: " << QuizManager::playerScore << endl;

		cout << endl;
		cout << "Please press enter to continue" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin.get(); //wait for the user to press enter
		
		return true;
	}
	else
	{
		cout << "Wrong answer!" << endl;

		cout << "The correct answer is: ";
		if (correctAnswer)
		{
			cout << "True" << endl;
		}
		else
		{
			cout << "False" << endl;
		}
		cout << endl;

		cout << "Please press enter to continue" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin.get(); //wait for the user to press enter	

		return false;
	}
}

void TrueFalseQuestion::DisplayQuestion() {
	
	cout << "True or False Question" << endl;
	std::string TempanswerIndex;
	std::cout << question << std::endl;
	for (int i = 0; i < 2; i++) {
		std::cout << i + 1 << ". " << answers[i] << std::endl;
	}
	std::cout << "Please chose one of the options" << std::endl;
	std::cin >> TempanswerIndex;
	try
	{
		int answerIndex = std::stoi(TempanswerIndex);
		if (answerIndex == 1 || answerIndex == 2)
		{
			Evaluate(answerIndex - 1); // -1 because the array starts from 0

		}
		else
		{
			system("cls"); //clean the screen
			DisplayQuestion();
		}
	}
	catch (const std::exception&)
	{
		system("cls"); //clean the screen
		DisplayQuestion();
	}
	
}
