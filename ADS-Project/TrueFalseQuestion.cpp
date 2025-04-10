#include <iostream>
#include "QuizQuestion.h"
#include "TrueFalseQuestion.h"
#include <string>

//constructor implementation
TrueFalseQuestion::TrueFalseQuestion(string newQuestion, bool answer, int points) {
	QuizQuestion::question = newQuestion;
	correctAnswer = answer;
	QuizQuestion::pointValue = points;
}

bool TrueFalseQuestion::Evaluate(bool answer) {
	return answer == correctAnswer;
}