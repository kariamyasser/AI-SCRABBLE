#include "TileLookUp.h"



TileLookUp::TileLookUp()
{
	letterMap['A'] = new int [2]{9, 1};
	letterMap['B']= new int [2]{2, 3};
	letterMap['C']= new int [2]{2, 3};
	letterMap['D']= new int [2]{4, 2};
	letterMap['E']= new int [2]{12, 1};
	letterMap['F']= new int [2]{2, 4};
	letterMap['G']= new int [2]{3, 2};
	letterMap['H']= new int [2]{2, 4};
	letterMap['I']= new int [2]{9, 1};
	letterMap['J']= new int [2]{1, 8};
	letterMap['K']= new int [2]{1, 5};
	letterMap['L']= new int [2]{4, 1};
	letterMap['M']= new int [2]{2, 3};
	letterMap['N']= new int [2]{6, 1};
	letterMap['O']= new int [2]{8, 1};
	letterMap['P']= new int [2]{2, 3};
	letterMap['Q']= new int [2]{1, 10};
	letterMap['R']= new int [2]{6, 1};
	letterMap['S']= new int [2]{4, 1};
	letterMap['T']= new int [2]{6, 1};
	letterMap['U']= new int [2]{4, 1};
	letterMap['V']= new int [2]{2, 4};
	letterMap['W']= new int [2]{2, 4};
	letterMap['X']= new int [2]{1, 8};
	letterMap['Y']= new int [2]{2, 4};
	letterMap['Z']= new int [2]{1, 10};
	letterMap[BLANK_TILE]= new int [2]{2, 0};
}


TileLookUp::~TileLookUp()
{
}

int TileLookUp::getFrequency(char c)
{
	return letterMap.find(c)->second[0];
}

int TileLookUp::getScore(char c)
{

//	cout << c << endl;
	return letterMap.find(c)->second[1];
}

void TileLookUp::setFrequency(char c,int f)
{
	letterMap.find(c)->second[0]= f;
}


