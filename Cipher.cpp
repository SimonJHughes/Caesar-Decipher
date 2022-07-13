#include "Cipher.h"
#include <iostream>

using namespace std;

//Sets cipher for shift. Takes in array of key values and size of array
void Cipher::setCipher(int arraySize, int inArray[])
{
	//Caps arraySize at 100, ignoring any after
	if(arraySize < 101)
	{
		keySize = arraySize;
	}
	else
	{
		cout << "Key bigger than 100. Only using first 100 values." << endl;
		keySize = 100;
	}
	//Fills key array with input array
	for(int i = 0; i < keySize; i++)
	{
		//Prevents negative numbers from being input
		if(!(inArray[i] >= 0))
		{
			cout << "No negative values >:(\nSetting to 0..." << endl;
			key[i] = 0;
			continue;
		}
		key[i] = inArray[i];
	}
	fillQueue();
}

//Takes in string then shifts characters using key
string Cipher::encodeMessage(string in)
{
	int tempNum;
	string returnString;
	bool lowerCase;

	//For each character in a string
	for(int i = 0; i < in.length(); i++)
	{
		//Sets flags if character at index i is uppercase or lowercase or a non-character
		if(in[i] < 91 && in[i] > 64)
		{
			lowerCase = false;
		}
		else if(in[i] > 96 && in[i] < 123)
		{
			lowerCase = true;
		}
		else
		{
			continue;
		}

		//Removes number from front of queue and places it in back
		tempNum = myQueue.dequeue();
		myQueue.enqueue(tempNum);

		//Handles key index being greater than 26
		tempNum = tempNum % 26;
		tempNum += in[i];

		//Wraps ASCII character around in case ASCII value is not a letter
		if(tempNum > 90 && !lowerCase)
		{
			tempNum -= 26;
		}
		else if(tempNum > 122 && lowerCase)
		{
			tempNum -= 26;
		}
		//Adds ciphered character to return string
		returnString.push_back(tempNum);
	}
	fillQueue();
	return returnString;
}

//Decodes encoded message of string in 
string Cipher::decodeMessage(string in)
{
	int tempNum;
	string returnString;
	bool lowerCase;

	//For each character in input string
	for(int i = 0; i < in.length(); i++)
	{
		//Sets lowercase flag depending on character's case
		if(in[i] < 91 && in[i] > 64)
		{
			lowerCase = false;
		}
		else if(in[i] > 96 && in[i] < 123)
		{
			lowerCase = true;
		}
		else
		{
			continue;
		}
		//Shifts character at index i by tempNum
		tempNum = myQueue.dequeue();
		myQueue.enqueue(tempNum);
		tempNum = tempNum % 26;
		tempNum = in[i] - tempNum;
		//Wraps ASCII
		if(tempNum < 65 && !lowerCase)
		{
			tempNum += 26;
		}
		else if(tempNum < 97 && lowerCase)
		{
				tempNum += 26;
		}
		returnString.push_back(tempNum);
	}
	fillQueue();
	return returnString;
}

//Resets queue to be equal to key
void Cipher::fillQueue()
{
	myQueue.clear();
	for(int i = 0; i < keySize; i++)
	{
		myQueue.enqueue(key[i]);
	}
}

//Returns pointer to key array
int* Cipher::getCipher()
{
	return key;
}

