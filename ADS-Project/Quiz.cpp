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

	//checking if the list is empty

	for (QuizQuestion* q : *myQuestions) {

		if (q != nullptr)
		{
			q->DisplayQuestion(); //displaying the question
		}
		else
		{
			cout << "The quiz is empty" << endl;			
		}
	}

	return true;
}
