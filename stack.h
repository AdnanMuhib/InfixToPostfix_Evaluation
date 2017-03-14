#pragma once
#include<iostream>
using namespace std;
class stack
{
public:
	stack();
	~stack();
	char arr[100];
	int top = -1;
	// Pop out the top element from the stack
	void pop();
	// Show the current status of the stack
	void show();
	// Returns true if the stack is empty
	bool empty();
	// Push data into the stack
	void push(char data);
};

