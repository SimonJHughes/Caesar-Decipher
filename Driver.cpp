#include "Cipher.h"
#include "CipherAdvanced.h"
#include <iostream>

using namespace std;

int main()
{
	CipherAdvanced myCipherAdvanced;
	int key[] = {3, 5, 6, 1};
	myCipherAdvanced.setCipher(4, key);
	string message = "buzzard";
	string encodedMessage = myCipherAdvanced.encodeMessage(message);
	cout << "Message encoded: " << encodedMessage << endl;
	cout << "Message decoded: " << myCipherAdvanced.decodeMessage(encodedMessage) << endl;
	myCipherAdvanced.encodeFile("data.txt");
	myCipherAdvanced.decodeFile("result.txt");
	

}