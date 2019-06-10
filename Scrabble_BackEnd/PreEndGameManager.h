#pragma once
#include "move.h"
#include "MonteCarlo.h"
#include "Board.h"
#include "Heuristics.h"
#include "ScoreManager.h"
#include "Gaddag.h"
#include <math.h>
#include <time.h>
class PreEndGameManager
{
	ScoreManager *scoreManager;
	Heuristics * Heu;
	Gaddag * MG;
	TileLookUp * TP;
	time_t startTime;
public:

	PreEndGameManager(TileLookUp * Tp, Gaddag * GD);
	~PreEndGameManager();
	Move GenerateMove();
	 int Blocking(vector<Move> *movesList, Rack * Rack, Board * b, ProbabilityManager * pm);
	double Fishing(const Move * move, Board * B, const vector<char>& RackLeave, Gaddag * MG, TileLookUp * Tup);
	Move * GoodEndGame();

	int calculateTimeLimit() const;

	void Stopwatch();

	void start();

	int elapsed() const;

	bool exceeded(int seconds) const;

};
