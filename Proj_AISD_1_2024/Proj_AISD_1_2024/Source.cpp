#include "Head.h"

int main() {
	int n;
	std::cin >> n;
	char temp[100];
	myString* formulas = new myString[n];
	for (int i = 0; i < n; i++) {
		while (true) {
			std::cin >> temp;
			if(temp[0] == '.')
				break;
			
			else {
				formulas[i].push(temp);
				formulas[i].push(' ');
			}
		}
	}
	for (int i = 0; i < n; i++) {
		RPN rpn;
		rpn.loadExpression(formulas[i]);
		
		//rpn.printInfixFormula();

		rpn.convertToPostfix();

		rpn.printPostfixFormula();

		rpn.calculate();
	}
}