#pragma once
#include <string>
using namespace std;

class Oper
{
private:
	char operation;
public:
	Oper(char operation);
	virtual float evaluate(float val1, float val2) = 0;
	string toString(void);
};

Oper* fromChar(char operation);

class Add : public Oper {
public:
	Add(char operation);
	float evaluate(float val1, float val2);
};

class Sub : public Oper {
public:
	Sub(char operation);
	float evaluate(float val1, float val2);
};

class Multi : public Oper {
public:
	Multi(char operation);
	float evaluate(float val1, float val2);
};

class Divide : public Oper {
public:
	Divide(char operation);
	float evaluate(float val1, float val2);
};

class Exponent : public Oper {
public:
	Exponent(char operation);
	float evaluate(float val1, float val2);
};