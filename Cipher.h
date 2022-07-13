#ifndef CIPHER_H
#define CIPHER_H
#include <string>
#include "Queue.h"

using namespace std;

class Cipher
{
private:
	int key[100];
	Queue myQueue;
	int keySize;
	void fillQueue();
public:
	void setCipher(int, int[]);
	int* getCipher();
	void printCipher();
	string encodeMessage(string in);
	string decodeMessage(string in);
};
#endif