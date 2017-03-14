#include<iostream>
#include<cstring>
#include<string>
#include<conio.h>
#include"stack.h"
#include"NumericOPs.h"
#include<Windows.h>
using namespace std;

// forward decalaration of the functions used functions

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Function that takes character array as input and converts to post fix
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void ConvertPostfix(char*);              

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Function that evaluates the output
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

float EvaluatePostfix(char*);

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Function that Performs the calculation on given operator and operands
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

float Calc(char, float, float); 

//++++++++++++++++++++++++++++++++++++++++++++++++
// function compares two operators and returns if 
//the op 1 has higher precedance than the second
//+++++++++++++++++++++++++++++++++++++++++++++++++

bool Precedence(char, char);

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Function that return the wight of the operator on basis of precedance
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

int Opweight(char);

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Function that checks whether the input char is an operator +,-,*
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool Operator(char);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Function that checks whether the input char is an operand abc...
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool Operand(char);                      

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// char array to store the postfix form of the infix and globally accesible
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

char postfix[100];

int main(){
	char op;
	stack st;
	char data;
	char infix[100];

	// interface

	string welcome = "Expression Evaluation using stack";
	for (int i = 0; i < welcome.length(); i++)
	{
		cout << welcome[i];
		Sleep(50);
	}
	
menu:
	cout << "\n";
	cout << "\t\t\t1 Push into the Stack." << endl;
	cout << "\t\t\t2 Pop from the Stack." << endl;
	cout << "\t\t\t3 Print Stack." << endl;
	cout << "\t\t\t4 Convert Infix to Postfix" << endl;
	cout << "\t\t\t5 Evaluate Infix expression" << endl;
	cout << "\t\t\t6 Exit" << endl;
	op = _getche();
	switch (op)
	{
	case '1':
	{
		system("cls");
		cout << "\t\tEnter  element to push : ";
		cin >> data;
		st.push(data);
		goto menu;
		break;
	}
	case '2':
	{
		system("cls");
		st.pop();
		goto menu;
		break;
	}	
	case '3':
	{
		system("cls");
		st.show();
		goto menu;
		break;
	}
	case '4':
	{
		system("cls");
		cout << endl << endl;
		cout << "\tKindly use on the following operators\n+,-,*,/,\,%: " << endl;
		cout << "\t\tKindly Enter the infix expression : ";
		cin.ignore();					// Ignore the \n character stored from the previous cin
		cin.getline(infix, 100);			// So that we can enter a line including spaces
		ConvertPostfix(infix);
		cout << "Postfix is : " << postfix << endl;
		goto menu;
		break;
	}
			
	case '5':
	{
		system("cls");
		cout << "\t\tKindly enter the infix expression: ";
		cin.getline(infix, 100);
		cout << "\t\tThe evaluated output is  " << EvaluatePostfix(infix) << endl;
		goto menu;
		break;
	}
	case '6':
	{
		system("cls");
		system("exit");
		break;
	}
	default:
	{
		system("cls");
		cout << "\t\twrong input try again :" << endl;
		goto menu;
		break;
	}
	}
}


void ConvertPostfix(char* expression){		// Takes the character array, and converts it to postfix
	stack st1;
	memset(&postfix[0], 0, sizeof(postfix));	// Flush out any previous stored data
	int j = 0;
	for (int i = 0; i<strlen(expression); i++)
	{
		//ignoring spaces
		if (expression[i] == ' ')
		{			
			continue;
		}

		else if (Operator(expression[i]))
		{			// If an operator, it is pushed into the stack after
			// popping out all higher precedence operators

			while (!st1.empty() && 
				st1.arr[st1.top] != '(' &&
				Precedence(st1.arr[st1.top],
				expression[i]))
			{
				postfix[j] = st1.arr[st1.top];
				st1.pop();
				j++;
			}
			st1.push(expression[i]);
		}
		else if (Operand(expression[i]))
		{		 // Appending operand to the postfix string
			postfix[j] = expression[i];
			j++;
		}
		else if (expression[i] == '(')
		{
			st1.push(expression[i]);
		}
		else if (expression[i] == ')')
		{		// pop out operators till opening bracket of the closed one is found
			while (!st1.empty() && st1.arr[st1.top] != '(')
			{
				postfix[j] = st1.arr[st1.top];
				j++;
				st1.pop();
			}
			if (!st1.empty())
			{
				st1.pop();
			}
		}
	}
	while (!st1.empty())
	{		// Appending the rest of the stack to the postfix expression!
		postfix[j] = st1.arr[st1.top];
		j++;
		st1.pop();
	}
}

bool Operator(char op)
{		// Returns true if the given parameter belongs to { =, -, *, /, % } --> Left Associative

	if (op == '+' || op == '-' || op == '*' || op == '/' || op == '%' || op == '^')
	{
		return true;
	}
	return false;
}

bool Operand(char op)
{			// Returns true if the given parameter belongs to { a-z OR A-Z )
	if ((op >= 'a' && op <= 'z') || (op >= 'A' && op <= 'Z'))
	{
		return true;
	}
	return false;
}

bool Precedence(char op1, char op2)
{	// It will return whether operator1 has higher precedence than operator2
	int weight1 = Opweight(op1);
	int weight2 = Opweight(op2);
	
	if (weight1 >= weight2)
	{		// As all operators are left associative
		return true;
	}
	return false;
}

int Opweight(char op)
{			// Returns the relative weight of the operators based on precedence order
	int weight = -1;
	switch (op)
	{
		case '-':
		case '+':
			weight = 1;
			break;
		case '/':
		case '*':
		case '%':
			weight = 2;
			break;
	}
	return weight;
}


float EvaluatePostfix(char* infix)
{		
	NumericOPs st;
	// First converting the infix to postfix before evaluating
	ConvertPostfix(infix);			
	float eval = 0, temp;
	for (int i = 0; i<sizeof(postfix); i++)
	{
		if (postfix[i] == ' ')
		{
			continue;
		}
		else if (Operator(postfix[i]))
		{
			float op2 = st.arr[st.top];
			st.pop();
			float op1 = st.arr[st.top];
			st.pop();
			float eval = Calc(postfix[i], op1, op2);	// Sending first two elements of stack, and the operator as arguments to the function
			st.push(eval);
		}
		else if (Operand(postfix[i]))
		{
			cout << " Enter the Value of  " << postfix[i] << " : ";
			cin >> temp;					// Asking the values of the  variables, at runtime!
			st.push(temp);
		}
	}
	return st.arr[st.top];
}

float Calc(char op, float op1, float op2){			// Performs the operation operator1 <operand> operator 2
	if (op == '+')
	{
		return op1 + op2;
	}
	else if (op == '-')
	{
		return op1 - op2;
	}
	else if (op == '*')
	{
		return op1*op2;
	}
	else if (op == '/')
	{
		return op1 / op2;
	}
	else if (op == '%')
	{
		return (int)op1 % (int)op2;
	}
	else if (op == '^')
	{
		return pow(op1, op2);
	}
	else{
		cout << "Kindly Re-check the input " << endl;
		return -1;
	}
	_getch();
}
