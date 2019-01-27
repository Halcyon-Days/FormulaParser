
#include "Expr.h"
#include "Term.h"
#include "Oper.h"
#include <map>

using namespace std;

Expr::Expr(Term* term1, Term* term2, Oper* operation) {
	this->term1 = term1;
	this->term2 = term2;
	this->operation = operation;
}

float Expr::evaluate(map<string, float> valueMap) {
	return operation->evaluate(term1->evaluate(valueMap), term2->evaluate(valueMap));
}

string Expr::toString() {
	return term1->toString()+ " " + operation->toString() + " " + term2->toString();
}
