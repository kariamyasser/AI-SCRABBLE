#pragma once
#include "Constants.h"
#include <unordered_set>
enum BonusSquareType { NoBonus = 0, LetterBonusX2, LetterBonusX3, WordBonusX2, WordBonusX3 };

class Square
{

public:
	char letter = EMPTY_SQUARE;//! blank tile has special character (check in constants file) , empty square equals null
	bool blank;
	
	//Timon 
	std::unordered_set<char> horizontalSet, verticalSet;


	//also it can be boolean with points=0 for no bonus but using enum is more clear
	BonusSquareType bonusType;
	Square(BonusSquareType bType = NoBonus);
	bool isEmpty() const {
		return letter == EMPTY_SQUARE;
	}
	bool isBlank()const {
		return letter == BLANK_TILE;
	}
	int getLetterMultiplier()const {
		return  bonusType == LetterBonusX2 or bonusType == LetterBonusX3? (int)bonusType+1:1;
	}
	int getWordMultiplier()const {
		return  bonusType == WordBonusX2 or bonusType == WordBonusX3 ? (int)bonusType-1 : 1;
	}
	~Square();
};
