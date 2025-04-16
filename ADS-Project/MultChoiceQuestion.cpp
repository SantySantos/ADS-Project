#include <iostream>
#include "QuizQuestion.h"
#include "MultChoiceQuestion.h"

using namespace std;

//constructor implementation
MultChoiceQuestion::MultChoiceQuestion(string newQuestion, string choices[4], int index, int points) {
	QuizQuestion::question = newQuestion;

	for (int i = 0; i < choices->size(); i++) {
		choiceArr[i] = choices[i];
	}

	answerIndex = index;
	QuizQuestion::pointValue = points;
}

//function implementation

bool MultChoiceQuestion::Evaluate(int index) {
	return index == answerIndex;
}