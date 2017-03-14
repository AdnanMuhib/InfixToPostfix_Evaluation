#include "stack.h"

stack::stack()
{
}


stack::~stack()
{
}
void stack::pop()
{
	if (empty()) {
		cout << "Empty Array :(" << endl << endl;
		return;
	}
	top--;
}


void stack::show()
{
	cout << endl << endl;
	if (empty())
	{
		cout << "\t\tArray is Empty" << endl << endl;
		return;
	}

	for (int i = 0; i <= top; i++) 
	{
		cout << arr[i] << "  ";
	}

	cout << endl << endl;
}

bool stack::empty()
{
	if (top<0) {
		return true;
	}
	return false;
}
void stack::push(char data)
{
	top++;
	arr[top] = data;
}
