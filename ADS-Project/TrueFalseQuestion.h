#pragma once

#include <iostream>
#include <string>
#include "QuizQuestion.h"

using namespace std;

class TrueFalseQuestion : public QuizQuestion {
private:
	//atributes
	bool correctAnswer;
	const std::string answers[2] = { "False", "True" }; // 0 = false, 1 = true
	
public:

	//constructor
	TrueFalseQuestion(string newQuestion, bool answer, int points);
	

	//functions
	bool Evaluate(bool answer);

	void DisplayQuestion();

};
