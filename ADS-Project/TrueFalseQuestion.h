#pragma once

#include <iostream>
#include <string>
#include "QuizQuestion.h"

using namespace std;

class TrueFalseQuestion : public QuizQuestion {
protected:
	//atributes
	bool correctAnswer;
	const std::string answers[2] = { "False", "True" }; // 0 = false, 1 = true
	
public:

	bool getAnswer();

	//constructor
	TrueFalseQuestion(string newQuestion, bool answer, int points);
	

	//functions
	bool Evaluate(bool answer);

	void DisplayQuestion();

	void DisplayStuff() override;
};
