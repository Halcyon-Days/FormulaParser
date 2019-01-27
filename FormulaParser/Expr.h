#pragma once

#include "Term.h"
#include "Oper.h"

using namespace std;

class Expr : public Term
{
private:
	Term* term1;
	Term* term2;
	Oper* operation;

public:	
	Expr(Term* term1, Term* term2, Oper* operation);
	Expr() {};
	virtual float evaluate(map<string, float> valueMap);
	string toString();
};

