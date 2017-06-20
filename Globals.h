#ifndef GLOBALS_H
#define GLOBALS_H
#include<string>
#include<iostream>

const int ARRAY_SIZE = 36;
int totalDataItems = 0; // track the total number of data items
int bstEffiencyCounter = 0;  // track how many operations it took to insert the data into the tree
int hashedTableEffiencyCounter = 0;  // track how many colision there are in the hashed table
int linkedListEffiencyCounter = 0;  // track how many operations it took to insert the data into the linked list


int getMenuInput(int size)
{
	int userInput = 0;
	std::string tempString;
	getline(std::cin, tempString);
	while ((tempString[0] < 49 || tempString[0] > (48 + size)) || tempString[1] != '\0')
	{
		std::cout << "1 - " << size << " are the only valid choices, try again: ";
		getline(std::cin, tempString);
	}
	userInput = stoi(tempString);
	return userInput;
}

int getIntegerInput()
{
	int number;
	std::string inputString;
	bool hasAlphaChars = false;
	getline(std::cin, inputString);
	for (unsigned int count = 0; count < (inputString.length()); count++)
		if (isdigit(inputString[count]) == 0)
		{
			hasAlphaChars = true;
		}
	while (hasAlphaChars || inputString == "\0" || inputString[0] == '-')
	{
		hasAlphaChars = false;
		std::cout << "only postive numbers are valid, try again: ";
		getline(std::cin, inputString);
		for (unsigned int count = 0; count < (inputString.length()); count++)
			if (isdigit(inputString[count]) == 0)
			{
				hasAlphaChars = true;
			}
	}
	number = stoi(inputString);
	return number;
}


#endif