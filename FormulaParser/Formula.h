#pragma once
#include <string>
#include <map>
#include <set>
#include "DataStructures.h"

using namespace std;

class Formula
{
private:
	Term* head;
	int numVariables;
	static map<int, set<char>> precedenceMap;
public:
	Formula(Term* head, int numVariables);
	float calculate(map<string, float> valueMap);
	string toString();
	Term* getHead() { return head; };
	int getNumVars() { return numVariables; };
};

Formula fromString(string s);
Formula fromFile(string fileName);
Formula parseFormulaFromLists(TermList* termList, OperList* operationList, int numVariables);