#include "QuizQuestion.h"
#include <iostream>

using namespace std;


//functions implementation
int QuizQuestion::getPoints() {
	return pointValue;
}

std::string QuizQuestion::getQuestion() {
	return question;
}

std::string QuizQuestion::setQuestion(const string& tempQuestion) 
{
	question = tempQuestion;
	return question;
}

bool QuizQuestion::Evaluate() {
	// This is a placeholder implementation. The actual implementation should be in derived classes.
	cout << "Evaluating question: " << question << endl;
	return true; // Default to true for now
}