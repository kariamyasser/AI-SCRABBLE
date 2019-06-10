#pragma once
#include "move.h"
#include "MonteCarlo.h"
#include "Board.h"
#include "Heuristics.h"
#include "ScoreManager.h"
#include "Gaddag.h"
#include <climits>
#include <math.h>
class MidGameManager
{
	ScoreManager *scoreManager;
	Heuristics * Heu;
	Gaddag * MG;
	TileLookUp * TP;

public:

	MidGameManager(TileLookUp * Tp, Gaddag * GD);
	~MidGameManager();
	int getBestMove( vector<Move>&  movesList, Rack* Rack, Board * b,bool& swap );

};
