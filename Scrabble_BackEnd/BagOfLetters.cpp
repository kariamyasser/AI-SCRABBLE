#include "BagOfLetters.h"
BagOfLetters::BagOfLetters() {
	bag[0] = 9;
	bag[1] = 2;
	bag[2] = 2;
	bag[3] = 4;
	bag[4] = 12;
	bag[5] = 2;
	bag[6] = 3;
	bag[7] = 2;
	bag[8] = 9;
	bag[9] = 1;
	bag[10] = 1;
	bag[11] = 4;
	bag[12] = 2;
	bag[13] = 6;
	bag[14] = 8;
	bag[15] = 2;
	bag[16] = 1;
	bag[17] = 6;
	bag[18] = 4;
	bag[19] = 6;
	bag[20] = 4;
	bag[21] = 2;
	bag[22] = 2;
	bag[23] = 1;
	bag[24] = 2;
	bag[25] = 1;
	bag[26] = 2;

	this->size = 100;
}

char BagOfLetters::draw()
{
	std::random_device rd;							// obtain a random number from hardware
	std::mt19937 eng(rd());							// seed the generator
	std::uniform_int_distribution<> distr(0, 26); // define the range inclusive
	int x = distr(eng);
	if (bag[x] == 0) {
		while (bag[x]==0)
		{
			std::random_device rd;							// obtain a random number from hardware
			std::mt19937 eng(rd());							// seed the generator
			std::uniform_int_distribution<> distr(0, 26); // define the range inclusive
			x = distr(eng);
		}
	}
	bag[x] -= 1;
	this->size -= 1;
	return mapping[x];
}

char* BagOfLetters::swap(char* x,int counter) {
	
	char* z = new char[counter];
	int i;
	for (i = 0; i < counter;++i)
	{
		char y = draw();
		z[i] = y;
	}
	for (i = 0; i < strlen(x); ++i) {
		bag[x[i] - 'A'] += 1;
	}
	this->size += counter;
	return z;
}

int BagOfLetters::getSize() {
	return this->size;
}

bool BagOfLetters::hasLetters() {
	return (this->size != 0);
}