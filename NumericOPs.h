#pragma once
#include<iostream>
using namespace std;
class NumericOPs
{
public:
	NumericOPs();
	~NumericOPs();
	float arr[100];
	int top = -1;
	// push numerics in stack
	void push(char data);
	// pop numerics in stack
	void pop(); 
	// print numerics in stack
	void show(); 
	// return true if stack is empty
	bool empty();
};

