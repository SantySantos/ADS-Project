#pragma once

#include <iostream>

class IEvaluable {
public:

	//abstract function
	virtual bool Evaluate() = 0;

	//virtual destructor
	virtual ~IEvaluable() = default;
};
