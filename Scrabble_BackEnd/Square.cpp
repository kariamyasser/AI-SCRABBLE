#include "Square.h"

Square::Square(BonusSquareType bType)
{
	bonusType = bType;
	letter = EMPTY_SQUARE;
	blank = false;
	int i;
	for (i = 0; i < 26; ++i)
	{
		verticalSet.insert(mapping[i]);
		horizontalSet.insert(mapping[i]);
	}
}

Square::~Square()
{
}