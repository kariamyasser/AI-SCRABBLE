#include "PreEndGameManager.h"



PreEndGameManager::PreEndGameManager( TileLookUp * Tp, Gaddag * GD)
{
	this->Heu = new Heuristics();
	this->MG = GD;
	this->TP = Tp;
}


PreEndGameManager::~PreEndGameManager()
{
}

Move PreEndGameManager::GenerateMove()
{
	return Move();
}

 int  PreEndGameManager::Blocking(vector<Move> * movesList, Rack* Rack, Board* b, ProbabilityManager *pm)
{
	string letters = b->getBoardLetters();
	char* boardpool = new char[letters.length()+1];	
	cout << "board pool size " << letters.length() << endl;
	letters.copy(boardpool, letters.size());
	boardpool[letters.length()] = '\0';
	//strcpy(boardpool ,letters.c_str());
	 int size = (*movesList).size();
//	cout <<"move list size"<<movesList.size() << endl;
	MonteCarlo * M = new MonteCarlo(Rack, boardpool, pm);
	vector<pair<vector<char>, double>> estimatedRackCost;
	estimatedRackCost.reserve(100);
	estimatedRackCost = M->simulation(100); //nehwal ne reserve
	 int BestMoveIndex = 0;
	 double BestScore = std::numeric_limits<int>::min();
	 double EstimatedScore = 0;
	start();

	vector<pair<Move, double>> blockingCosts;
	blockingCosts.reserve(size);
	for (int i = 0; i < size; i++)
	{
	//	cout << i << endl;
			double costestimated = 0;
		 double weightestimated = 0;
		//MY SCORE 
		 double myScore = ScoreManager::calculateScore((*movesList)[i], b,this->TP);

		// Future
		 double futureScore = (double)this->Heu->preEnd((*movesList)[i], Rack->getLeave((*movesList)[i]), Rack->getUniqueLeave((*movesList)[i]));
		b->commitMove((*movesList)[i]);
		b->computeCrossSets(MG->root);
		 double opponentScore = 0;
		 double Weights = 0;
		 double fishingFuture = 0.0f;
		vector<char> rackleave;
		rackleave.reserve(7);
		rackleave = Rack->getLeave((*movesList)[i]);
		vector<Move>allMoves; 
		MG->findWords(M->availableCharacters,allMoves, b);
		int allMovesSize = allMoves.size();
		allMovesSize = (allMovesSize > 100) ? 100 : allMovesSize;
		int estimatedRackSize = estimatedRackCost.size();
		for (int indexOfAllMoves = 0; indexOfAllMoves < allMovesSize; indexOfAllMoves++) {
			double probablity = 0.0;
			sort((allMoves[indexOfAllMoves].chars).begin(), (allMoves[indexOfAllMoves].chars).end());
		//	cout << "ESTIMATED RACK SIZE :" << estimatedRackSize << endl;
			for (int indexEstimatedRack = 0; indexEstimatedRack < estimatedRackSize; indexEstimatedRack++) {
			//	cout << "i entereeed " << endl;
				if (includes(estimatedRackCost[indexEstimatedRack].first.begin(), estimatedRackCost[indexEstimatedRack].first.end(), (allMoves[indexOfAllMoves].chars).begin(), (allMoves[indexOfAllMoves].chars).end()))
				{
					probablity += estimatedRackCost[indexEstimatedRack].second *1000.0;

				
				}
			//		cout << " PROP :" << estimatedRackCost[indexEstimatedRack].second  *10000.0<< endl;
				Weights += estimatedRackCost[indexEstimatedRack].second*1000.0;
			}
			
		//out <<  " PROP " << probablity << endl;
			fishingFuture += Fishing(&allMoves[indexOfAllMoves], b, rackleave, this->MG, TP);
			opponentScore += (probablity *ScoreManager::calculateScore(allMoves[indexOfAllMoves], b, TP));
		}
		if (Weights == 0 || isnan(Weights)) {
		//	cout << "KOSOMO "<<Weights << endl;
			//system("pause");
			opponentScore = 0;
		}
		else
		opponentScore = opponentScore / Weights;
		fishingFuture = fishingFuture/(double)allMovesSize;
		BestMoveIndex = (BestScore < myScore + futureScore + fishingFuture - opponentScore) ? i : BestMoveIndex;
		BestScore = (BestScore < myScore + futureScore+ fishingFuture - opponentScore) ? myScore + fishingFuture +futureScore - opponentScore : BestScore;
		cout << "Best Score " << BestScore << " MY SCORE: " << myScore << " future Score: " << futureScore << "opponentScore: " << opponentScore <<"Fishing score "<< fishingFuture << endl;
		if (exceeded(120)) {
			
			cout <<endl<< "the movements we reached is " << i << "and the best score "<< BestScore << endl;
			break;

		}
		b->uncommitMove((*movesList)[i]);
				}
//	delete M;
	return BestMoveIndex;

}

 inline double   PreEndGameManager::Fishing( const Move *move, Board * B,const vector<char> &RackLeave, Gaddag* MG, TileLookUp* Tup)
{
	 B->commitMove(*move);
	B->computeCrossSets(MG->root);
//	cout <<"entered fisihing procedure" << endl;
	vector<Move> moveList;
	MG->findWords(RackLeave,moveList, B);
	double maxScorePerMove = 0.0f;
	int sizeMoveList = moveList.size();
	sizeMoveList = (sizeMoveList > 100) ? 100 : sizeMoveList;
	for (int i = 0; i < sizeMoveList; i++) {   //eb2a zabtha le el Size !!!
		double score = ScoreManager::calculateScore(moveList[i], B, Tup);
		maxScorePerMove +=score ;
	}
	B->uncommitMove(*move);
	maxScorePerMove /= double(sizeMoveList);

	
	return  (maxScorePerMove);
}




Move * PreEndGameManager::GoodEndGame()
{
	return NULL;
}

const int timeLimitPerSecondsPerTurn = 60;

int PreEndGameManager::calculateTimeLimit() const
{
	return 100;
}
void PreEndGameManager::Stopwatch()
	
{
	start();
}

void PreEndGameManager::start()
{
	this->startTime = time(NULL);
}

int PreEndGameManager::elapsed() const
{
	time_t now = time(NULL);
	return (int)(now - this->startTime);
}

bool PreEndGameManager::exceeded(int seconds) const
{
	//cout <<endl<<"time Elapsed"<< (elapsed()) << endl;
	return elapsed() > seconds;
}
