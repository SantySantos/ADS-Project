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

MultChoiceQuestion::MultChoiceQuestion(string newQuestion, string choice1, string choice2, string choice3, string choice4, int index, int points)
{
	QuizQuestion::question = newQuestion;
	choiceArr[0] = choice1;
	choiceArr[1] = choice2;
	choiceArr[2] = choice3;
	choiceArr[3] = choice4;
	answerIndex = index;
	QuizQuestion::pointValue = points;
}
//function implementation

bool MultChoiceQuestion::Evaluate(int index) {
	return index == answerIndex;
}