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
	//number of arguments inside each currently open parenthesis
	Stack<int> argCounts;

	for (int i = 0; i < infixFormula.getSize(); i++) {
		char firstSymbol = infixFormula[i][0];
		if (firstSymbol >= '0' && firstSymbol <= '9')
			out.push(infixFormula[i]);
		else if (firstSymbol == 'I' || firstSymbol == 'M' || firstSymbol == 'N')
			stack.push(infixFormula[i]);
		else if (firstSymbol == ',') {
			while(!(stack.top() == "("))
				out.push(stack.pop());
			argCounts.push(argCounts.pop() + 1);
		}
		else if (firstSymbol == '(') {
			stack.push(infixFormula[i]);
			argCounts.push(1);
		}
		else if (firstSymbol == ')') {
			while (!(stack.top() == "("))
				out.push(stack.pop());
			stack.pop();
			int args = argCounts.pop();
			//MIN/MAX take any number of arguments, so store the count in the token (e.g. MIN3)
			if (!stack.isEmpty() && stack.top()[0] == 'M') {
				bool isMin = stack.pop()[1] == 'I';
				char buffer[20];
				snprintf(buffer, sizeof(buffer), "%s%d", isMin ? "MIN" : "MAX", args);
				stack.push(myString(buffer));
			}
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
			snprintf(buffer, sizeof(buffer), "%d", result);
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
			snprintf(buffer, sizeof(buffer), "%d", result);
			stack.push(buffer);
		}
		else if (firstSymbol == 'M') {
			//token is MINn / MAXn, where n is the number of arguments
			bool isMin = postfixFormula[i][1] == 'I';
			int args = 0;
			for (int k = 3; k < postfixFormula[i].getSize(); k++)
				args = args * 10 + (postfixFormula[i][k] - '0');
			std::cout << postfixFormula[i] << " ";
			for (int i = stack.getSize() - 1; i >= 0; i--)
			{
				std::cout << stack[i] << " ";
			}
			std::cout << std::endl;
			Vector<int> values;
			for (int k = 0; k < args; k++)
				values.push(stack.pop().toInt());
			int result = isMin ? min(values) : max(values);
			char buffer[20];
			snprintf(buffer, sizeof(buffer), "%d", result);
			stack.push(buffer);
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
				snprintf(buffer, sizeof(buffer), "%d", result);
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
				snprintf(buffer, sizeof(buffer), "%d", result);
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
				snprintf(buffer, sizeof(buffer), "%d", result);
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
					snprintf(buffer, sizeof(buffer), "%d", result);
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
