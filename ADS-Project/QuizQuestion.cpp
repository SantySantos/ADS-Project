#include "QuizQuestion.h"
#include <iostream>
#include <string>
#include "MultChoiceQuestion.h"
#include "TrueFalseQuestion.h"


using namespace std;


//functions implementation
int QuizQuestion::getPoints() {
	return pointValue;
}

std::string QuizQuestion::getQuestion() {
	return question;
}

std::string QuizQuestion::setQuestion(const std::string& tempQuestion) 
{
	question = tempQuestion;
	return question;
}

void QuizQuestion::DisplayQuestion() {
	
}
bool QuizQuestion::Evaluate() {
	// This is a placeholder implementation. The actual implementation should be in derived classes.
	cout << "Evaluating question: " << question << endl;
	return true; // Default to true for now
}