#pragma once

#include <iostream>
#include <string>
#include "IEvaluable.h"

using namespace std;

class QuizQuestion : public IEvaluable {

protected:
	//atributes
	string question;

public:
	
	//attributes
	int pointValue;

	 string getQuestion();

	void DisplayQuestion();

	std::string setQuestion(const std::string& tempQuestion); 

	//functions
	int getPoints();

	bool Evaluate() override;
};