#include "Term.h"
#include "Expr.h"
#include <map>

using namespace std;

Number::Number(float value) {
	this->value = value;
}

float Number::evaluate(map<string, float> valueMap) {
	return value;
}

string Number::toString() {
	return to_string(value);
}

Tag::Tag(string value) {
	this->value = value;
}

float Tag::evaluate(map<string, float> valueMap) {
	return valueMap[value];
}

string Tag::toString() {
	return value;
}
