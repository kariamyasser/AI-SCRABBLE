#pragma once
#include "Board.h"
#include "TileLookUp.h"
#include "move.h"
#include <cmath>
class ScoreManager
{
public:
	// Parameters
	Board * boardManager;
	TileLookUp * tileLookUp;

	// Methods
		//timon|
	static	double calculateScore( Move & m, Board * board,  TileLookUp * tileLookUp);
	ScoreManager(Board*, TileLookUp*);
	
	~ScoreManager();
};