#pragma once
#include "myString.h"
#include "Stack.h"
#include "Queue.h" 
//reversed polish notation
class RPN
{
private:
	int addition(int a, int b);
	int subtraction(int a, int b);
	int multiplication(int a, int b);
	bool division(int a, int b,int& result);
	int _if(int a, int b, int c);
	int negation(int a);
	int min(Vector<int> a);
	int max(Vector<int> a);

	Vector<myString> infixFormula;
	Vector<myString> postfixFormula;
	Queue<myString> postfixQueue;
	Stack<int> stack;
	int priority(char c){
		if(c=='(')
			return 0;
		else if(c=='+'||c=='-')
			return 1;
		else if(c=='*'||c=='/')
			return 2;
		else if(c=='I'||c=='N'||c=='M')
			return 3;
		else if(c==')')
			return 4;
		else
			return -1;
	};
	public:
	RPN();
	~RPN();
	void convertToPostfix();
	void printPostfixFormula();
	void printInfixFormula();
	void loadExpression(myString expression);
	void calculate();
};