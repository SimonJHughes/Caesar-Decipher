#include "CipherAdvanced.h"
#include <fstream>
#include <ostream>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

//Encodes text in given fileName and outputs to result.txt
void CipherAdvanced::encodeFile(string fileName)
{
	ifstream inFile(fileName);
	string fileContents;
	char inputChar;
	//Adds each character in text file to string
	while(inFile.get(inputChar))
	{
		fileContents.push_back(inputChar);
	}
	ofstream outFile("result.txt");
	//Encodes entire string and outputs
	outFile << encodeMessage(fileContents);
	outFile.close();
	inFile.close();
}

//Decodes encoded file
void CipherAdvanced::decodeFile(string fileName)
{
	ifstream inFile(fileName);
	string fileContents;
	char inputChar;
	//Adds each character in text file to string
	while(inFile.get(inputChar))
	{
		fileContents.push_back(inputChar);
	}
	ofstream outFile("result.txt");
	//Decodes entire string and outputs
	outFile << decodeMessage(fileContents);
	outFile.close();
	inFile.close();
}


//Start of unknownScramble functions

//Takes in scrambled word and attempts to unscramble it
void CipherAdvanced::unknownScramble(string in)
{
	cout << "Attempting to descramble " << in << "..." << endl;
	vector<string> positiveMatches;
	vector<int> positiveKeys;
	ifstream inFile;
	int counter = 0;
	string tempString;
	inFile.open(existingDictFile());

	//If dictionary file is good, try and unscramble
	if(inFile.good())
	{
		int testKey[4];
		buildVector(in);
		for(int i = 0; i < 27; i++)
		{
			cout << i << "/26" << endl;
			for(int j = 0; j < 27; j++)
			{
				//If length of word is 4 letters or more, take the third and fourth letter shifted
				//by i and j and call optimize with those characters
				if(sameLengthWords[0].length() > 3 && i > 0 && j > 0)
				{
					testKey[3] = i;
					testKey[2] = j;
					setCipher(4, testKey);
					tempString = decodeMessage(in);
					optimize(tempString[3], tempString[2]);
				}
				for(int k = 0; k < 27; k++)
				{
					for(int l = 0; l < 27; l++)
					{
						//Set the cipher to every possible combination
						testKey[0] = l;
						testKey[1] = k;
						testKey[2] = j;
						testKey[3] = i;
						setCipher(findKeySize(testKey), testKey);
						//Compares decoded message to each viable word
						for(int m = 0; m < viableSize; m++)
						{
							if(decodeMessage(in) == viableWords[m])
							{
								counter++;
								positiveMatches.push_back(viableWords[m]);
								positiveKeys.push_back(l);
								positiveKeys.push_back(k);
								positiveKeys.push_back(j);
								positiveKeys.push_back(i);
							}
						}
					}
				}
			}
		}
		//If there are no solutions, print this to outfile
		if(counter > 0)
		{
			for(int i = 0; i < counter; i++)
			{
				cout << positiveMatches[i] << " with key ";
				cout << positiveKeys[i * 4] << " " << positiveKeys[i * 4 + 1] << " " << positiveKeys[i * 4 + 2] << " " << positiveKeys[i * 4 + 3] << endl;
			}
		}
		if(counter == 0)
		{
			cout << "NO POSSIBILITIES EXIST\n";
		}
	}
	else
	{
		cout << "No dictionary file found." << endl;
	}
}

//Returns string containing path to dictionary file
string CipherAdvanced::existingDictFile()
{
	string testString = "/usr/share/dict/words";
	ifstream inFile(testString);
	if(inFile.good())
	{
		inFile.close();
		return testString;
	}
	testString = "/usr/dict/words";
	inFile.open(testString);
	if(inFile.good())
	{
		inFile.close();
		return testString;
	}
	return "Custom path to dictionary file here";
}

//Returns the key size to use in setCipher given an array
int CipherAdvanced::findKeySize(int inArray[])
{
	if(inArray[1] == 0 && inArray[2] == 0 && inArray[3] == 0)
	{
		return 1;
	}
	if(inArray[2] == 0 && inArray[3] == 0)
	{
		return 2;
	}
	if(inArray[3] == 0)
	{
		return 3;
	}
	return 4;
}

//Populates a vector that contains all words with the same length as the message to be decoded
void CipherAdvanced::buildVector(string inString)
{
	ifstream inFile(existingDictFile());
	int stringLength = inString.length();
	string testWord;
	int counter;
	while(inFile >> testWord)
	{
		if(testWord.length() == stringLength)
		{
			counter++;
			sameLengthWords.push_back(testWord);
		}
	}
	sameLengthSize = counter;
}

//Finds all words in sameLengthWords and populates viableWords vector with words
//that have the same characters at index 2 and 3
void CipherAdvanced::optimize(char inputChar, char secondInputChar)
{
	vector<string> tempVector;
	viableSize = 0;
	int counter = 0;
	for(int i = 0; i < sameLengthSize; i++)
	{
		string testString = sameLengthWords[i];
		if(testString[3] == inputChar && testString[2] == secondInputChar)
		{
			counter++;
			tempVector.push_back(sameLengthWords[i]);
		}
	}
	viableWords.clear();
	for(int i = 0; i < counter; i++)
	{
		viableSize++;
		viableWords.push_back(tempVector[i]);
	}
}