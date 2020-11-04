#include "stack.h"
#include <string>


bool bracketCheck(const std::string& s)
{
	Stack *newStack = new Stack();

	char curr;

	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == '{' || s[i] == '(' || s[i] == '[')
		{
			newStack->push(s[i]);
		}

		if (s[i] == '}' || s[i] == ')' || s[i] == ']')
		{
			if (newStack->isEmpty())
				return false;

			char last = newStack->top();

			if (s[i] == '}' && last == '{' || s[i] == ')' && last == '(' || s[i] == ']' && last == '[')
				newStack->pop();
			else
				return false;
		}
	}

	return newStack->isEmpty();
}
