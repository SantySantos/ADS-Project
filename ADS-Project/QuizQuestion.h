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

<<<<<<< HEAD
	string setQuestion(const string& tempQuestion); 
=======
	std::string setQuestion(const std::string& tempQuestion); 
>>>>>>> 99797b2685ba06bbad9e740a9e26320182ae7cd4

	//functions
	int getPoints();

	bool Evaluate() override;
};