#pragma once

#include <iostream>
#include <string>
#include "IEvaluable.h"

using namespace std;

class QuizQuestion : public IEvaluable {

protected:
	//atributes
	std::string question;

public:
	
	//attributes
	int pointValue;

	std::string getQuestion();

	std::string setQuestion(const std::string& tempQuestion); 

	//functions
	int getPoints();

	bool Evaluate() override;
};