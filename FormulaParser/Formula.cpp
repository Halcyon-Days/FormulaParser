#include "Formula.h"
#include <fstream>
#include <set>
#include <regex>

using namespace std;

//control precedence and operations in forming of formula
//lower numbers mean higher precedence
map<int, set<char>> precedenceMap = {
	{0, {'^'}},
	{1, {'*', '/'}},
	{2, {'+','-'}}
};

regex regexOperators = regex("[\\+\\-\\*\\/\\^]");
regex regexBracketStart = regex("[\[\{\(]");
regex regexBracketEnd = regex("[\\]\}\)]");

Formula::Formula(Term* head, int numVariables) {
	this->head = head;
	this->numVariables = numVariables;
}

float Formula::calculate(map<string, float> valueMap) {
	//quick check if values corrospond to terms in term
	if (valueMap.size() != numVariables) {
		throw invalid_argument("Invalid list of values.");
	}
	else {
		return head->evaluate(valueMap);
	}
}

string Formula::toString() {
	return head->toString();
}

int reduceNestedBrackets(char* token, char **context,  TermList* termList) {
	string subString = "";
	CharStack* bracketStack = new CharStack;
	bracketStack->push(token[0]);

	while (bracketStack->size > 0) {
		token = strtok_s(NULL, " ", context);

		if (token == NULL) {
			throw std::invalid_argument("Bad Formula string given!");
		}
		else if (regex_match(token, regexBracketStart)) {
			bracketStack->push(token[0]);
		}
		else if (regex_match(token, regexBracketEnd)) {
			bracketStack->pop();
		}

		
		if (bracketStack->size > 0) {
			subString += token;
			subString += " ";
		}
	}

	Formula subFormula = fromString(subString);
	termList->add(subFormula.getHead());

	return subFormula.getNumVars();
}

Formula fromString(string s) {
	TermList* termList = new TermList;
	OperList* operationList = new OperList;

	char *context;
	int numVariables = 0;

	//splits string by spaces, and parses each token into the term or expression list
	char* token = strtok_s(const_cast<char*> (s.c_str()), " ", &context);
	while (token != NULL) {
		if (token == "") {
			//skip if invalid empty string
		}
		else if (regex_match(token, regexBracketStart)) {
			numVariables += reduceNestedBrackets(token, &context, termList);
		}
		//token is operator
		else if (regex_match(token, regexOperators)) {
			operationList->add(token[0]);
		}
		else {
			Term* newTerm;
			//token is number
			if (strtof(token, NULL) != 0 || !strcmp(token, "0") || !strcmp(token, "0.0")) {
				newTerm = new Number(strtof(token, NULL));
			}
			//token is a tag
			else {
				newTerm = new Tag(token);
				numVariables++;
			}

			termList->add(newTerm);
		}
		//get next token
		token = strtok_s(NULL, " ", &context);
	}

	return parseFormulaFromLists(termList, operationList, numVariables);
}

Formula parseFormulaFromLists(TermList* termList, OperList* operationList, int numVariables) {
	set<char> currentOperations;
	OperNode* currentOperNode;
	TermNode* currentTermNode;

	//iterates for the number of precedence levels in map
	for (auto precedence : precedenceMap) {
		currentOperations = precedence.second;
		currentOperNode = operationList->start;
		currentTermNode = termList->start;

		//starting from the beginning of both lists, iterate through all the nodes
		while (currentOperNode != NULL) {
			//if current operation is part of current precedence level, create new expression
			if (currentOperations.find(currentOperNode->o->toString()[0]) != currentOperations.end()) {
				termList->reduceTermsToExpr(currentTermNode, currentTermNode->next, currentOperNode);
				OperNode* nextOperNode = currentOperNode->next;
				operationList->remove(currentOperNode);
				currentOperNode = nextOperNode;
			}
			//else skip to next nodes
			else {
				currentOperNode = currentOperNode->next;
				currentTermNode = currentTermNode->next;
			}
		}
	}
		return Formula(termList->start->t, numVariables);
}

Formula fromFile(string fileName) {
	string s;
	ifstream file(fileName);
	if (file.is_open()) {
		getline(file, s);
	}
	file.close();
	return fromString(s);
}
