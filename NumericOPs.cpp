#include "NumericOPs.h"



NumericOPs::NumericOPs()
{
}
NumericOPs::~NumericOPs()
{
}
void NumericOPs::push(char data)
{
	top++;
	arr[top] = data;
}

void NumericOPs::pop()
{
	if (top == -1)
	{
		cout << endl;
		cout << "\t\tArray is Empty" << endl << endl;
		return;
	}
	top--;
}
void NumericOPs::show()
{
	cout << endl << endl;
	if (top == -1)
	{
		cout << "Array is Empty" << endl << endl;
		return;
	}

	for (int i = 0; i <= top; i++) {
		cout << arr[i] << "  ";
	}

	cout << endl << endl;
}

bool NumericOPs::empty()
{
	if (top<0) {
		return true;
	}
	return false;
}