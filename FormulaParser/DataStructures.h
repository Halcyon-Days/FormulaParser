#include "Term.h"
#include "Oper.h"
#include "Expr.h"

struct CharNode {
public:
	char c;
	CharNode* next;
	CharNode(char c);
};

struct OperNode {
public:
	Oper* o;
	OperNode* next;
	OperNode* previous;
};

struct OperList {
public:
	OperNode* start;
	OperNode* end;
	OperList();
	void add(char o);
	void remove(OperNode* o);
};

struct TermNode {
public:
	Term* t;
	TermNode* next;
};

struct TermList {
public:
	TermNode* start;
	TermNode* end;
	TermList();
	void add(Term* t);
	void reduceTermsToExpr(TermNode* t1, TermNode* t2, OperNode* o);
};

struct CharStack {
private:
	CharNode* head;

public:
	int size;
	CharStack(void);
	void push(char c);
	void pop(void);
};
