#include "RPN.h"

RPN::RPN()
{
}

RPN::~RPN()
{
}

void RPN::loadExpression(myString expression)
{
	//read until ' ' and push to infixFormula
	//if ' ' then push to infixFormula
	myString temp;
	for (int i = 0; i < expression.getSize(); i++)
	{
		
		if (expression[i] == ' ')
		{
			infixFormula.push(temp);
			temp.clear();
		}
		else
		{
			temp.push(expression[i]);
		}
	}
	
}

void RPN::convertToPostfix() {
	Stack<myString> stack;
	Queue<myString> out;
	
	for (int i = 0; i < infixFormula.getSize(); i++) {
		char firstSymbol = infixFormula[i][0];
		if (firstSymbol >= '0' && firstSymbol <= '9')
			out.push(infixFormula[i]);
		else if (firstSymbol == 'I' || firstSymbol == 'M' || firstSymbol == 'N')
			stack.push(infixFormula[i]);	
		else if (firstSymbol == ',') {
			while(!(stack.top() == "("))
				out.push(stack.pop());
		}
		else if (firstSymbol == '(')
			stack.push(infixFormula[i]);
		else if (firstSymbol == ')') {
			while (!(stack.top() == "("))
				out.push(stack.pop());
			stack.pop();
		}
		else
		{
				while(true)
				{
					if (!stack.isEmpty())
						if(priority(stack.top()[0]) >= priority(firstSymbol))
						out.push(stack.pop());
						else
							break;
					else
						break;
				}
			stack.push(infixFormula[i]);
		}
	}
	while (!stack.isEmpty())
		out.push(stack.pop());
	while(!out.isEmpty())
		postfixFormula.push(out.pop());
}

void RPN::calculate()
{
	Stack<myString> stack;
	for (int i =0 ; i < postfixFormula.getSize(); i++) {
		char firstSymbol = postfixFormula[i][0];
		if(firstSymbol>='0'&& firstSymbol <= '9')
			stack.push(postfixFormula[i]);
		else if (firstSymbol == 'I') {
			std::cout << "IF ";
			for (int i = stack.getSize() - 1; i >= 0; i--)
			{
				std::cout << stack[i] << " ";
			}
			std::cout << std::endl;
			int c = stack.pop().toInt();
			int b = stack.pop().toInt();
			int a = stack.pop().toInt();
			int result = _if(a, b, c);
			char buffer[20];
			sprintf(buffer, "%d", result);
			stack.push(buffer);
		}
		else if (firstSymbol == 'N') {
			std::cout << "N ";
			for (int i = stack.getSize() - 1; i >= 0; i--)
			{
				std::cout << stack[i] << " ";
			}
			std::cout << std::endl;
			int a = stack.pop().toInt();
			int result = negation(a);
			char buffer[20];
			sprintf(buffer, "%d", result);
			stack.push(buffer);
		}
		else if (firstSymbol == 'M') {
			if (postfixFormula[i] == "MIN")
			{
				//TODO min
			}
			else if (postfixFormula[i] == "MAX")
			{
				//TODO max
			}
		}
		else {
			
			if (firstSymbol == '+')
			{
				std::cout << "+ ";
				for (int i = stack.getSize()-1; i >=0; i--)
				{
					std::cout << stack[i] << " ";
				}
				std::cout << std::endl;
				int b = stack.pop().toInt();
				int a = stack.pop().toInt();
				int result = addition(a, b);
				char buffer[20];
				sprintf(buffer, "%d", result);
				stack.push(buffer);
			}
			else if (firstSymbol == '-')
			{
				std::cout << "- ";
				for (int i = stack.getSize() - 1; i >= 0; i--)
				{
					std::cout << stack[i] << " ";
				}
				std::cout << std::endl;
				int b = stack.pop().toInt();
				int a = stack.pop().toInt();
				int result = subtraction(a, b);
				char buffer[20];
				sprintf(buffer, "%d", result);
				stack.push(buffer);
			}
			else if (firstSymbol == '*')
			{
				std::cout << "* ";
				for (int i = stack.getSize() - 1; i >= 0; i--)
				{
					std::cout << stack[i] << " ";
				}
				std::cout << std::endl;
				int b = stack.pop().toInt();
				int a = stack.pop().toInt();
				int result = multiplication(a, b);
				char buffer[20];
				sprintf(buffer, "%d", result);
				stack.push(buffer);
			}
			else if (firstSymbol == '/')
			{
				std::cout << "/ ";
				for (int i = stack.getSize() - 1; i >= 0; i--)
				{
					std::cout << stack[i] << " ";
				}
				std::cout << std::endl;
				int b = stack.pop().toInt();
				int a = stack.pop().toInt();
				int result;
				bool error = division(a, b,result);
				if (error)
					goto errorDivisionByZero;
				else 
				{
					char buffer[20];
					sprintf(buffer, "%d", result);
					stack.push(buffer);
				}
			}
		}
	}
	std::cout<<stack.pop().toInt();
	std::cout << std::endl;
errorDivisionByZero:
	
	return;
}

inline int RPN::addition(int a, int b)
{
	
	return a+b;
}

inline int RPN::subtraction(int a, int b)
{
	
	return a-b;
}

inline int RPN::multiplication(int a, int b)
{
	
	return a*b;
}

inline bool RPN::division(int a, int b,int& result)
{
	
	if(b!=0)
		result=floor( a/b);
	else {
		std::cout << "ERROR";
		std::cout << std::endl;
		return true;
	}
	return false;
}
void RPN::printPostfixFormula()
{
	for (int i = 0; i < postfixFormula.getSize(); i++)
	{
		std::cout << postfixFormula[i] << " ";
	}
	std::cout << std::endl;
}

void RPN::printInfixFormula()
{
	for (int i = 0; i < infixFormula.getSize(); i++)
	{
		std::cout << infixFormula[i] << " ";
	}
	std::cout << std::endl;
}

inline int RPN::_if(int a, int b, int c)
{
	if(a>0)
		return b;
	else
		return c;
}

inline int RPN::negation(int a)
{
	return -a;
}

inline int RPN::min(Vector<int> a)
{
	int min = a[0];
	for (int i = 1; i < a.getSize(); i++)
	{
		if(a[i] < min)
			min = a[i];
	}
	return min;
}

inline int RPN::max(Vector<int> a)
{
	int max = a[0];
	for (int i = 1; i < a.getSize(); i++)
	{
		if(a[i] > max)
			max = a[i];
	}
	return max;
}
