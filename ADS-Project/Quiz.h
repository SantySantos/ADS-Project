#pragma once

#include <iostream>
#include <string>
#include <list>
#include "QuizQuestion.h"
#include "IEvaluable.h"

using namespace std;

class Quiz : public IEvaluable {

public:
	//constructor
	Quiz();

	//atributes
	list<QuizQuestion*>* myQuestions = new list<QuizQuestion*>;


	std::string quizName;

	//functions

	//To be implemented

	/*
	int CalculateResult(int score);

	void ShuffleQuestions();

	static void CreateQuiz(std::string Path);
	*/

	bool Evaluate() override;

};