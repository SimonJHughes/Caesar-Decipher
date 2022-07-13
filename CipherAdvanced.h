#ifndef CIPHERADVANCED_H
#define CIPHERADVANCED_H
#include <string>
#include <vector>
#include "Cipher.h"

class CipherAdvanced : public Cipher
{
public:
	void encodeFile(string);
	void decodeFile(string);
	void unknownScramble(string);
private:
	string existingDictFile();
	int findKeySize(int[]);
	vector<string> viableWords;
	vector<string> sameLengthWords;
	void buildVector(string);
	void optimize(char, char);
	int sameLengthSize;
	int viableSize;
};

#endif