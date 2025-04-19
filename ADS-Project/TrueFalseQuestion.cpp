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
		QuizManager::playerScore += pointValue; //adding the points to the score
		return true;
	}
	else
	{
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