#pragma once

#include <iostream>
#include <string>
#include "QuizQuestion.h"

using namespace std;

class TrueFalseQuestion : public QuizQuestion {
private:
	//atributes
	bool correctAnswer;

public:

	//constructor
	TrueFalseQuestion(string newQuestion, bool answer, int points);
	

	//functions
	bool Evaluate(bool answer);

};
