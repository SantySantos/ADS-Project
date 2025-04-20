#pragma once
#include "QuizQuestion.h"
#include <iostream>
#include <string>

using namespace std;

class MultChoiceQuestion : public QuizQuestion {

public:

	//atributes
	std::string choiceArr[4];

	int answerIndex;
	//constructor
	//MultChoiceQuestion(string newQuestion, string choices[4], int index, int points);

	MultChoiceQuestion(string newQuestion, string choice1, string choice2, string choice3, string choice4, int index, int points);
	//functions
	bool Evaluate(int index);

	void DisplayQuestion() override;

};