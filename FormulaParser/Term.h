#pragma once
#include <map>
#include <string>

using namespace std;

class Term
{
public:
	Term() {};
	virtual float evaluate(map<string, float> valueMap) = 0;
	virtual string toString() = 0;
};

class Number : public Term {
private:
	float value;
public:
	Number(float value);
	float evaluate(map<string, float> valueMap);
	string toString();
};

class Tag : public Term {
private:
	string value;
public:
	Tag(string tag);
	float evaluate(map<string, float> valueMap);
	string toString();
};