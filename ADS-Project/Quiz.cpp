#include "Quiz.h"
#include <iostream>
#include "MultChoiceQuestion.h"
#include "TrueFalseQuestion.h"
#include "QuizManager.h"

using namespace std;

//constructor implementation
Quiz::Quiz() {

}


//function implementation
bool Quiz::Evaluate() {

	//checking if the list is empty

	for (QuizQuestion* q : *myQuestions) {

		system("cls"); //clean the screen
		cout << "Current Score: " << QuizManager::playerScore << endl; //displaying the current score
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
