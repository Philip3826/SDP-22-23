#include "solution.h"

#include <cassert>
#include <cmath>
#include <stdexcept>
#include <stack>

#include <iostream>

/// Performs an operation on two arguments
///
/// @param operation
///    The code of the operation as a character. Can be +, -, *, / or ^
///
/// @param left
///    First argument of the operation 
///
/// @param right
///    Second argument of the operation
///
/// @exception std::invalid_argument
///    If an invalid operation is passed to the function or
///    if the operation is division (/) and the right argument is 0.
///
double perform(char operation, double left, double right)
{
	switch(operation) {
		case '+': return left + right;
		case '-': return left - right;
		case '*': return left * right;
		case '^': return std::pow(left, right);
		case '/':
			if(right == 0)
				throw std::invalid_argument("Division by zero");
			return left / right;
		
		default:
			throw std::invalid_argument("Invalid operation symbol passed to perform()");
	}
}

double evaluateRpn(const char* rpn)
{
	//TODO Complete this function
	if (!rpn) throw std::invalid_argument("nullptr as argument");
	if (*rpn == '\0') return 0;
	std::stack<double> rpnStack;
	
	size_t i = 0;
	
	while (rpn[i])
	{
		if (isDigit(rpn[i])) rpnStack.push(toDouble(rpn[i]));
		
	    if (isOperation(rpn[i]))
		{
			if (rpnStack.size() < 2) throw std::invalid_argument("invalid operation");

			double right = rpnStack.top();
			rpnStack.pop();
			double left = rpnStack.top();
			rpnStack.pop();

			double result = perform(rpn[i], left, right);
			rpnStack.push(result);
		}
		
		if (!isDigit(rpn[i]) && !isOperation(rpn[i])) throw std::invalid_argument("");

		i++;
	}

	if (rpnStack.size() == 1) return rpnStack.top();
	else throw std::invalid_argument("invalid expression");
	
}
