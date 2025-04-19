#include "Quiz.h"
#include <iostream>

using namespace std;

//constructor implementation
Quiz::Quiz() {

}


//function implementation
bool Quiz::Evaluate() {
	//attributes
	int score = 0;

	//could change to template type for MultChoiceQuestion and TrueFalseQuestion
	for (QuizQuestion* q : *(myQuestions)) {
		if (q->Evaluate()) {
			score++;
		}
		else {
			score--;
		}
	}
	if (score < myQuestions->size() / 2) {
		return false;
	}
	return true;
}