#pragma once

#include <iostream>
#include <string>
#include "IEvaluable.h"

class QuizQuestion : public IEvaluable {

protected:
	//atributes
	std::string question;

public:
	
	//attributes
	int pointValue;

	std::string getQuestion();

	//functions
	int getPoints();

	bool Evaluate() override;
};