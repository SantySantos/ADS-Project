#include "Quiz.h"
#include <iostream>
#include "MultChoiceQuestion.h"
#include "TrueFalseQuestion.h"

using namespace std;

//constructor implementation
Quiz::Quiz() {

}


//function implementation
bool Quiz::Evaluate() {
	//attributes
	int score = 0;

	for (QuizQuestion q : myQuestions) 
	{			
		q.DisplayQuestion(); //displaying the question
	}

	return true;
}
