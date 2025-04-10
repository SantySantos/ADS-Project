#pragma once
#include "QuizQuestion.h"
#include <iostream>
#include <string>

using namespace std;

class MultChoiceQuestion : public QuizQuestion {

private:

	//atributes
	std::string choiceArr[4];

	int answerIndex;

public:

	//constructor
	MultChoiceQuestion(string newQuestion, string choices, int index, int points);

	//functions
	bool Evaluate(int index);

};