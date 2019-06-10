#pragma once
//Board, Rack, Move, Score
#include "Board.h"
#include "Rack.h"
#include "move.h"
#include <fstream>
#include <vector>
class ML
{

public:
	ML();
	void Write2File(Board &board, Rack &rack, Move &m, int score, bool append = true);
	~ML();
};

