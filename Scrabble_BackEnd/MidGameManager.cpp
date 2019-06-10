#include "MidGameManager.h"



MidGameManager::MidGameManager(TileLookUp * Tp, Gaddag * GD)
{
	this->Heu = new Heuristics();
	this->MG = GD;
	this->TP = Tp;
}


MidGameManager::~MidGameManager()
{
}

int MidGameManager::getBestMove( vector<Move> & movesList, Rack* Rack, Board * b,bool& swap)
{

	int size = movesList.size();
	cout << "Move Count: " << size << endl;
	int bestMoveIndex = -1;
	long double BestScore = LONG_MIN;
	//long double EstimatedScore = 0;
	long double moveScore;
	long double heuristicScore;
	bool firstTurn = b->getBoardLetters().length() == 0;

	double maxRackLeave = 0.0;
	double maxLeaveAndScore = 0.0;
	int indexMaxLeave = 0;
	int indexMaxLeaveScore = 0;

	for (int i = 0; i < size; i++) {

		// Move Score
		moveScore = ScoreManager::calculateScore(movesList[i], b, this->TP);
		//		cout << "Raw Score: " << moveScore << endl;

				// Heuristic Score
		heuristicScore = this->Heu->midGame(firstTurn, movesList[i], Rack->getLeave(movesList[i]), Rack->getUniqueLeave(movesList[i]));
		//cout << "Heuristic Score: " << heuristicScore << endl;

		double rackLeave = this->Heu->Double_RL(movesList[i], Rack->getLeave(movesList[i]), Rack->getUniqueLeave(movesList[i]));
		double leaveAndScore = rackLeave + moveScore;

		if (rackLeave > maxRackLeave)
		{
			maxRackLeave = rackLeave;
			indexMaxLeave = i;
		}

		if (leaveAndScore > maxLeaveAndScore)
		{
			maxLeaveAndScore = leaveAndScore;
			indexMaxLeaveScore = i;
		}

		// Total Score
		moveScore += heuristicScore;
		//cout << "Total Score: " << moveScore << endl;

		if (moveScore > BestScore) {
			BestScore = moveScore;
			bestMoveIndex = i;
		}
	}

	//cout << "Highest Score Move: " << BestScore << endl;
	swap = false;
	int swapIndex = 0;

	if (indexMaxLeave != indexMaxLeaveScore)
	{
		if (maxRackLeave > maxLeaveAndScore)
		{
			swap = true;
			swapIndex = indexMaxLeave;
		}
	}
	else
	{
		if (maxRackLeave >= (maxLeaveAndScore - maxRackLeave))
		{
			swap = true;
			swapIndex = indexMaxLeave;
		}
	}
	cout << "Max Rack leave is " << maxRackLeave << " Max leave and score " << maxLeaveAndScore << endl;
	cout << "swap is " << swap << endl;
///	if (swap) {

	//	if (b->m_board[7][7].isEmpty())
	//	{
//			swap = false;
//			return bestMoveIndex;
//		}
	//	else {
		//	return swapIndex;
//		}
//	}
	return bestMoveIndex;
}
