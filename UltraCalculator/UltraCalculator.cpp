#include "pch.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

void gotoxy(int xpos, int ypos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos; scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput, scrn);
}

void addition(char(&number1)[150], char(&number2)[150], char(&number3)[150], int system)
{
	for (int i = 149; i > 0; i--)
	{
		number3[i] += ((number1[i] == 0) ? 0 : (number1[i] - ((number1[i] > 57) ? 55 : 48))) 
					+ ((number2[i] == 0) ? 0 : (number2[i] - ((number2[i] > 57) ? 55 : 48)));
		if (number3[i] >= system)
		{
			number3[i - 1]++;
			number3[i] -= system;
		}
	}
}

void subtraction(char(&number1)[150], char(&number2)[150], char(&number3)[150], int system)
{
	for (int i = 0; i < 150; i++)
	
		if (number2[i] > number1[i])
		{
			for (int j = i; j < 150; j++)
			{
				number2[j] += number1[j];
				number1[j] = number2[j] - number1[j];
				number2[j] -= number1[j];
			}
			cout << "Numbers are reversed\n";
			break;
		}
	

	for (int i = 149; i > 0; i--)
	{
		number3[i] += ((number1[i] == 0) ? 0 : (number1[i] - ((number1[i] > 57) ? 55 : 48)))
					- ((number2[i] == 0) ? 0 : (number2[i] - ((number2[i] > 57) ? 55 : 48)));
		if (number3[i] < 0)
		{
			number3[i - 1]--;
			number3[i] += system;
		}
		if ((number1[i - 1] == 0) && (number2[i - 1] == 0))
			break;
	}
}

void multiplication(char(&number1)[150], char(&number2)[150], char(&number3)[150], int system)
{
	int symbolCounter = 0;
	bool done = false;
	
	for (int i = 0; i < 150; i++)
		number2[i] = (number2[i] == 0) ? 0 : (number2[i] - ((number2[i] > 57) ? 55 : 48));

	number2[149]--;
	for (int i = 149; i > symbolCounter - 1; i--)
	{
		if (number2[i] < 0)
		{
			number2[i - 1]--;
			number2[i] += system;
		}
	}
	while (number2[symbolCounter] == 0)
		symbolCounter++;
	while (!done)
	{
		for (int i = 149; i > 0; i--)
		{
			number3[i] += (number1[i] == 0) ? 0 : (number1[i] - ((number1[i] > 57) ? 55 : 48));
			if (number3[i] >= system)
			{
				number3[i - 1]++;
				number3[i] -= system;
			}
		}
		number2[149]--;
		for (int i = 149; i > symbolCounter-1; i--)
			if (number2[i] < 0)
			{
				number2[i - 1]--;
				number2[i] += system;
			}
		
		for (int i = 2; i < 150; i++)
			if (number2[i] < 0)
				done = true;
	}
}

void division(char(&number1)[150], char(&number2)[150], char(&number3)[150], int system)
{
	bool done = false;
	for (int i = 0; i < 150; i++)
		number1[i] = (number1[i] == 0) ? 0 : (number1[i] - ((number1[i] > 57) ? 55 : 48));
	while (!done) 
	{
		for (int i = 149; i > 0; i--)
		{
			number1[i] -= ((number2[i] == 0) ? 0 : (number2[i] - ((number2[i] > 57) ? 55 : 48)));
			if (number1[i] < 0)
			{
				number1[i - 1]--;
				number1[i] += system;
			}
		}
		number3[149]++;
		for (int i = 149; i > 0; i--)
			if (number3[i] >= system)
			{
				number3[i - 1]++;
				number3[i] -= system;
			}
		done = true;
		for (int i = 0; i < 150; i++)
			if (number1[i] != 0)
				done = false;
	}
}

long long int convertToDec(char(&number)[150], int system)
{
	long long int decNumber = 0, tempDecNumber = 0;
	short int exp = 0;
	for (int i = 149; i >= 0; i--)
	{
		if (number[i])
			decNumber += (number[i] - ((number[i] > 57) ? 55 : 48)) * pow(system, exp);
		exp++;
		if (tempDecNumber > decNumber)
		{
			decNumber = -1;
			break;
		}
		tempDecNumber = decNumber;
	}
	return decNumber;
}

int main()
{
	char numberA[150] = {0}, numberB[150] = {0}, numberC[150] = {0};
	char sNumeralSystem[3] = { 0 };
	short int symbolCounter = 0, numeralSystem = 0;
	bool done = false;
	char ch = 0, operation = 0;
	unsigned long long int decNumber = 0;
	bool divisionByZero = false;

	while (ch != 27) 
	{
		for (int i = 0; i < 150; i++)
			numberA[i] = numberB[i] = numberC[i] = 0;
		system("cls");
		ch = 0;
		done = false;
		symbolCounter = 0;
		for (int i = 0; i < 3; i++)
			sNumeralSystem[i] = 0;
		while (!done)
		{
			
			system("cls");
			cout << "Enter numeral system:\n";
			for (int i = 0; i < 3; i++)
			{
				cout << sNumeralSystem[i];
				if (sNumeralSystem[i + 1] == 0)
					break;
			}
			ch = _getch();
			if ((ch == 8) && (symbolCounter > 0))
			{
				symbolCounter--;
				sNumeralSystem[symbolCounter] = 0;
			}
			if ((ch >= 48) && (ch <= 57) && (symbolCounter < 2))
			{
				sNumeralSystem[symbolCounter] = ch;
				symbolCounter++;
			}
			numeralSystem = atoi(sNumeralSystem);
			if ((numeralSystem > 1) && (numeralSystem < 37) && (ch == 13))
				done = true;
		}

		system("cls");
		ch = 0;
		symbolCounter = 0;
		while (ch != 13)
		{
			system("cls");
			cout << "Enter first number:\n";
			for (int i = 0; i < 150; i++)
			{
					cout << numberA[i];
					if (numberA[i+1] == 0)
						break;
			}
			ch = _getch();
			if ((ch == 8) && (symbolCounter > 0))
			{
				numberA[symbolCounter] = 0;
				symbolCounter--;
				
			}
			if ((symbolCounter < 149) && (ch > 47))
				if ((ch < 48 + numeralSystem) || ((ch > 64) && (ch < 55 + numeralSystem)))
				{	
					numberA[symbolCounter+1] = ch;
					symbolCounter++;
				}
		}
		for (int i = 0; i <= symbolCounter; i++)
		{
			numberA[149 + i - symbolCounter] = numberA[i];
			numberA[i] = 0;
		}
		
		symbolCounter = 0;
		while ((numberA[symbolCounter] == 0) || (numberA[symbolCounter] == 48))
		{
			numberA[symbolCounter] = 0;
			symbolCounter++;
		}

		system("cls");
		ch = 0;
		symbolCounter = 0;
		while (ch != 13)
		{
			system("cls");
			cout << "Enter second number:\n";
			for (int i = 0; i < 150; i++)
			{
				cout << numberB[i];
				if (numberB[i + 1] == 0)
					break;
			}
			ch = _getch();
			if ((ch == 8) && (symbolCounter > 0))
			{
				numberB[symbolCounter] = 0;
				symbolCounter--;
			}
			if ((symbolCounter < 149) && (ch > 47))
				if ((ch < 48 + numeralSystem) || ((ch > 64) && (ch < 55 + numeralSystem)))
				{
					numberB[symbolCounter + 1] = ch;
					symbolCounter++;
				}
		}
		for (int i = 0; i <= symbolCounter; i++)
		{
			numberB[149 + i - symbolCounter] = numberB[i];
			numberB[i] = 0;
		}
		
		symbolCounter = 0;
		while ((numberB[symbolCounter] == 0) || (numberB[symbolCounter] == 48))
		{
			numberB[symbolCounter] = 0;
			symbolCounter++;
		}

		operation = 0;
		done = false;
		while (!done)
		{
			system("cls");
			cout << "Choose sign of operation:\n";
			ch = 0;
			cin >> ch;
			if ((ch == 42) || (ch == 43) || (ch == 45) || (ch == 47))
				operation = ch;
			if (((operation == 42) || (operation == 43) || (operation == 45) || (operation == 47)))
				done = true;
		}
		system("cls");

		for (int i = 0; i < 150; i++)
			if (numberA[i] != 0)
				cout << numberA[i];
		cout << "  (" << (decNumber = convertToDec(numberA, numeralSystem)) << ")";
		cout << '\n' << ch << '\n';
		for (int i = 0; i < 150; i++)
			if (numberB[i] != 0)
				cout << numberB[i];
		cout << "  (" << (decNumber = convertToDec(numberB, numeralSystem)) << ")\n=\n";
		divisionByZero = true;
		switch (operation)
		{
			case 42:
				multiplication(numberA, numberB, numberC, numeralSystem);
				break;
			case 43:
				addition(numberA, numberB, numberC, numeralSystem);
				break;
			case 45:
				subtraction(numberA, numberB, numberC, numeralSystem);
				break;
			case 47:
				for (int j = 0; j < 149; j++)
					if ((numberB[149] != 0) && ((numberB[j] != 0)  || (numberB[149] != 48)))
						divisionByZero = false;
				if (!divisionByZero)
					division(numberA, numberB, numberC, numeralSystem);
				else 
				{
					system("cls");
					cout << "Error: division by zero\n";
				}
				break;
		}

		if (((!divisionByZero && (ch == 47)) || (ch != 47)) && 
			!(((numberA[149] == 48) && (numberA[148] == 0)) || ((numberB[149] == 48) && (numberB[148] == 0))))
		{
			symbolCounter = 0;
			while ((numberC[symbolCounter] == 0) && (symbolCounter < 149))
				symbolCounter++;

			for (int i = symbolCounter; i < 150; i++)
				numberC[i] += (numberC[i] > 9) ? 55 : 48;

			for (int i = 0; i < 150; i++)
				if (numberC[i] != 0)
					cout << numberC[i];
			decNumber = convertToDec(numberC, numeralSystem);
			if (decNumber != -1)
				cout << "  (" << decNumber << ")\n";
			else
				cout << "  (Ooh... Too big number)\n";
		}
		system("pause");
	}
	return 0;
}
