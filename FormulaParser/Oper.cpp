#include "Oper.h"
#include <math.h>
#include <fstream>
using namespace std;

Oper::Oper(char operation) {
	this->operation = operation;
}

string Oper::toString(void) {
	return string() + operation;
}

Oper* fromChar(char operation) {
	Oper* newOperation;
	if (operation == '+') {
		newOperation =  new Add(operation);
	} else if (operation == '-') {
		newOperation = new Sub(operation);
	} else if (operation == '*') {
		newOperation = new Multi(operation);
	} else if (operation == '/') {
		newOperation = new Divide(operation);
	} else if (operation == '^') {
		newOperation = new Exponent(operation);
	} else {
		throw std::invalid_argument("Invalid operand type.");
	}

	return newOperation;
}

Add::Add(char operation) : Oper(operation) {}
float Add::evaluate(float val1, float val2) {
	return val1 + val2;
}

Sub::Sub(char operation) : Oper(operation) {}
float Sub::evaluate(float val1, float val2) {
	return val1 - val2;
}

Multi::Multi(char operation) : Oper(operation) {}
float Multi::evaluate(float val1, float val2) {
	return val1 * val2;
}

Divide::Divide(char operation) : Oper(operation) {}
float Divide::evaluate(float val1, float val2) {
	return val1 / val2;
}

Exponent::Exponent(char operation) : Oper(operation) {}
float Exponent::evaluate(float val1, float val2) {
	return pow(val1, val2);
}
