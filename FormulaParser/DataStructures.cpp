#include "DataStructures.h"


CharNode::CharNode(char c) {
	this->c = c;
	this->next = NULL;
}


OperList::OperList() {
	start = NULL;
	end = NULL;
}

void OperList:: add(char o) {
	OperNode* newOperation = new OperNode;
	newOperation->o = fromChar(o);
	newOperation->next = NULL;
	newOperation->previous = end;

	if (start == NULL) {
		start = newOperation;
		end = newOperation;
	}
	else {
		end->next = newOperation;
		end = newOperation;
	}
}

void OperList::remove(OperNode* o) {
	OperNode* nextOperNode = o->next;
	//operation nodes are trickier, we dont "fold" them like the term nodes, so this covers cases of reassigning pointers wrong
	if (start == o) {
		start = nextOperNode;
	}
	else {
		o->previous->next = nextOperNode;
		if (nextOperNode != NULL) {
			nextOperNode->previous = o->previous;
		}
	}

	free(o);
}

TermList::TermList() {
	start = NULL;
	end = NULL;
}

void TermList::add(Term* t) {
	TermNode* newTermNode = new TermNode;
	newTermNode->t = t;
	newTermNode->next = NULL;

	if (start == NULL) {
		start = newTermNode;
		end = newTermNode;
	}
	else {
		end->next = newTermNode;
		end = newTermNode;
	}
}

void TermList::reduceTermsToExpr(TermNode* t1, TermNode* t2, OperNode* o) {
	Expr* newExpr = new Expr(t1->t, t2->t, o->o);

	//we reduce the 2 current term nodes into 1 expression, replace the first term node with this and free the other
	t1->t = newExpr;
	t1->next = t2->next;
	free(t2);
}

CharStack::CharStack(void) {
	this->head = NULL;
	this->size = 0;
}

void CharStack::push(char c) {
	CharNode* node = new CharNode(c);
	node->next = this->head;
	this->head = node;
	this->size++;
}

void CharStack::pop(void) {
	if (size > 0) {
		head = head->next;
		this->size--;
	}
	else {
		throw std::out_of_range("Stack is empty!");
	}
}
