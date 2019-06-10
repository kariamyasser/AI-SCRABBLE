#include "EndSimulation.h"
#include <limits>
#include "Play.h"
#include "move.h"
#include <vector>
#include "Board.h"
#include <algorithm>
#include <iostream>

bool myfunctionmax(BStarNode i, BStarNode j) { return (i.optm > j.optm && !i.closed || (i.optm == j.optm && i.pess > j.pess)); }
bool myfunctionmin(BStarNode i, BStarNode j) { return (i.optm < j.optm); }
bool isaltern(BStarNode i, BStarNode j) { return (i.optm > j.optm); }

long EndSimulation::id = 0;
//get best move when depth=0 and terminating condition not met with all branches visited
//return index of best move
int getBestMove(vector<BStarNode> &moves)
{

	//if 2 nodes have same optimistic values choose node with smallest range (best node)
	BStarNode *bestBStarNode = &moves[0];
	int bestNodeIndex = 0;
		//get first best optm
	for (int i = bestNodeIndex + 1; i < moves.size() && moves[i].optm==moves[0].optm; i++)
	{
		if (moves[i].pess > bestBStarNode->pess)// check smaller range
			bestNodeIndex;
	}
	return bestNodeIndex;

}

double getMaxPessimistic(vector<BStarNode> moves)
{
	double max = moves[0].pess;
	for (size_t i = 1; i < moves.size(); i++)
	{
		if (moves[i].pess > max)
			max = moves[i].pess;
	}
	return max;
}
double getBestPessimisticMin(vector<BStarNode> moves)
{
	double min = moves[0].pess;
	for (size_t i = 1; i < moves.size(); i++)
	{
		if (moves[i].pess < min)
			min = moves[i].pess;
	}
	return min;
}

void getBestFirstAndSecondMax(vector<BStarNode>&moves, vector<BStarNode *>& bestFirstAndSecond)
{
	double maxOptm = -1000000000000;
	double maxaltern = -20000000000;
	BStarNode *bestBStarNode = NULL;
	BStarNode *alternBStarNode = NULL;
	for (size_t i = 0; i < moves.size(); i++)
	{
		if (!moves[i].closed)
		{
			if (moves[i].optm > maxOptm)
			{
				maxaltern = maxOptm;
				alternBStarNode = bestBStarNode;
				maxOptm = moves[i].optm;
				bestBStarNode = &moves[i];
			}
			else if (moves[i].optm == maxOptm)
			{
			if (moves[i].pess > bestBStarNode->pess)// check smaller range
				bestBStarNode = &moves[i];
			}
			else if (moves[i].optm > maxaltern)
			{
			maxaltern = moves[i].optm;
			alternBStarNode = &moves[i];
			}
		}
	}
	if (bestBStarNode != NULL)
		bestFirstAndSecond.push_back(bestBStarNode);
	if (alternBStarNode != NULL)
		bestFirstAndSecond.push_back(alternBStarNode);

}
void getBestFirstAndSecondMin(vector<BStarNode>&moves, vector<BStarNode *>& bestFirstAndSecond)
{
	double minOptm = DBL_MAX - 1;
	double minaltern = DBL_MAX;
	BStarNode *bestBStarNode = NULL;
	BStarNode *alternBStarNode = NULL;
	for (size_t i = 0; i < moves.size(); i++)
	{
		if (!moves[i].closed)
		{
			if (moves[i].optm < minOptm)
			{
				minaltern = minOptm;
				alternBStarNode = bestBStarNode;
				minOptm = moves[i].optm;
				bestBStarNode = &moves[i];
			}
			else if (moves[i].optm == minOptm)
			{
				if (moves[i].pess < bestBStarNode->pess)// check smaller range
					bestBStarNode = &moves[i];
			}
			else if (moves[i].optm < minaltern) {//altern node
				minaltern = moves[i].optm;
				alternBStarNode = &moves[i];
			}
		}
	}
	if (bestBStarNode != NULL)
		bestFirstAndSecond.push_back(bestBStarNode);
	if (alternBStarNode != NULL)
		bestFirstAndSecond.push_back(alternBStarNode);

}
void EndSimulation::getOpRack()
{
	//TileLookUp tl;
	//unordered_map<char, int>lookup;
	//int frq=0;
	//for (const char&letter : board->getBoardLetters())
	//{
	//	frq=tl.getFrequency(letter);

	//}
}
bool isRackHaveQ_Z(const Rack&rack)
{
	for (size_t i = 0; i < rack.list.size(); i++)
	{
		if (rack.list[i] == 'Q' || rack.list.size() == 'Z')
			return true;
	}
	return false;
}

bool moveHasLetter2(const Move&move, char letter) {
	for (size_t i = 0; i < move.Plays.size(); i++)
	{
		if (move.Plays[i].Letter == letter)
			return true;
	}
	return false;

}
double Qsticking2(const vector<char>& estimatedRack, const Move& move, const vector<pair<int, int>>&  Qpos, const vector<pair<int, int>>&  Zpos)
{

	//vector<Play> plays = move.Plays;

	double quality = 0;
	int i, ilen;


	for (i = 0, ilen = move.Plays.size(); i < ilen; i++)
	{

			int k, klen;
			for (k = 0, klen = Qpos.size(); k < klen; k++)
			{
				if (move.Plays[i].coordinates == Qpos[k])
				{
					quality = quality + 5;
				}

			}
	}
	return quality;
}

vector<BStarNode>* EndSimulation::getChildren(const BStarNode &node, Rack& myrack, Rack&oprack, bool ismax, vector<BStarNode *>& bestFirstAndSecond)
{
	if ((ismax && myrack.list.size() == 0) || (!ismax && oprack.list.size() == 0))
	{
		vector<BStarNode>&cachevector = cache[node.id];
		cachevector = {};
		return &cachevector;
	}
	if (cache.find(node.id) != cache.end()) //node expanded before
	{
		//TODO:set bestfirstandsecond by iterating over cache vector and get max not closed nodes
		vector<BStarNode>& moves = cache[node.id];
		if (ismax)
			getBestFirstAndSecondMax(moves, bestFirstAndSecond);
		else
			getBestFirstAndSecondMin(moves, bestFirstAndSecond);
		//
		return &cache[node.id]; //? check if children have the same vector by reference
	}
	//node first expand
	vector<BStarNode>&cachevector = cache[node.id];
	int bestBStarNodeindex = -1;
	int alternBStarNodeindex = -1;
	//TODO: calc score with heuristic
	//get max 2 moves
	//max node
	vector<pair<int, int>> qPos = {};//TODO:
	vector<pair<int, int>> zPos{};//TODO:
	//q_z positions are used only if I am max and my op has Q or Z ,same in opposite
	bool opRackHaveQ = isRackHaveQ_Z(oprack);
	bool myRackHaveQ = isRackHaveQ_Z(myrack);

	if ((ismax && opRackHaveQ) || (!ismax && myRackHaveQ))
	{
		for (size_t i = 0; i < 15; i++)
		{
			for (size_t j = 0; j < 15; j++)
			{
				if (board->m_board[i][j].horizontalSet.find('Q') != board->m_board[i][j].horizontalSet.end())
					qPos.push_back(pair<int, int>(j, i));
				else if (board->m_board[i][j].horizontalSet.find('Z') != board->m_board[i][j].horizontalSet.end())
					zPos.push_back(pair<int, int>(j, i));
			}
		}
	}

	// end q,z
	//? what if all nodes have same optim value what altern will be?
	if (ismax) {
		
		vector<Move> moves;
		MG->findWords(myrack.getRackTiles(), moves, board);
		double maxOptm = -100000;
		double maxaltern = -20000;
		double bestPess = -100000;
		for (size_t i = 0;i< moves.size(); i++)
		{
			//! improvement: not all nodes executed so ,board should not be created for all nodes ,just the 1st and 2nd node

			double moveScore = ScoreManager::calculateScore(moves[i], board, tileLookup);
			double optm, pess;
			hr->endGame2vals(oprack.getRackTiles(),myRack, moves[i], qPos, zPos, optm, pess);
			optm += moveScore;
			pess += moveScore;
			double mul = 1;
			if (opRackHaveQ) {

				mul+=Qsticking2(oprack.getRackTiles(), moves[i], qPos, zPos);
			}
			if (moveHasLetter2(moves[i],'Q'))
			{
				cout << "MIN" << optm << " " << pess << endl;
				mul += QVAL;
			}
			if (moveHasLetter2(moves[i], 'Z'))
			{
				mul += ZVAL;
			}
			if (moveHasLetter2(moves[i], 'J'))
			{
				mul += JVAL;
			}
			optm += mul;
			pess += mul;

			//Move move = moves[i];
			//double test = optm;
			/*if (moves[i].Plays[0].Letter == 'T' && moves[i].Plays.size()==1)
				cout << "T move:" << optm;*/
			//if (moveHasQ(moves[i]))
			//{
			//	//cout << "MIN" << optm << " " << pess<<endl;
			//	optm *= HASQVAL;
			//	pess *= HASQVAL;
			//	/*cout << move.Plays[0].coordinates.second<<","<< move.Plays[0].coordinates.first<<endl;
			//	cout << optm << "," << pess<<endl;*/

			//}
			//else if (moveHasZ(moves[i]))
			//{
			//	optm *= HASZVAL;
			//	pess *= HASZVAL;
			//}
			//else if (qPos.size() != 0)
			//{
			//	int val = Qsticking(moves[i], qPos, zPos);
			//	//cout << "val: "<<val;
			//	optm *= val;
			//	pess *= val;

			//	//cout <<"row,col " <<moves[i].Plays[0].coordinates.second << "," << moves[i].Plays[0].coordinates.first << endl;
			//	//cout << optm << "," << pess << endl;
			//}
			BStarNode tempnode(optm, pess,moveScore, id++, moves[i]);
			//cout << test;
			cachevector.push_back(tempnode);
			if (optm > maxOptm)
			{
				maxaltern = maxOptm;
				maxOptm = optm;
				alternBStarNodeindex = bestBStarNodeindex;
				bestBStarNodeindex = (int)cachevector.size()-1;
			}
			else if (optm == maxOptm)
			{
				if (pess > cachevector[bestBStarNodeindex].pess)// check smaller range
					bestBStarNodeindex =(int) cachevector.size() - 1;
			}
			else if (optm > maxaltern)
			{
				maxaltern = optm;
				alternBStarNodeindex = (int) cachevector.size() - 1;
			}
		}
	}
	else {

		vector<Move> moves;
		MG->findWords(oprack.getRackTiles(),moves, board);
		double bestPess = 10000;
		double minOptm = DBL_MAX - 1;
		double minaltern = DBL_MAX;
		for (size_t i = 0; i < moves.size(); i++)
		{

			//! improvement: not all nodes executed so ,board should not be created for all nodes ,just the 1st and 2nd node
			double moveScore = ScoreManager::calculateScore(moves[i], board, tileLookup);
			double optm, pess;
			hr->endGame2vals(myrack.getRackTiles(),oprack, moves[i], qPos, zPos, pess, optm);
			optm += moveScore;
			pess += moveScore;
			double mul = 1;
			if (myRackHaveQ) {

				mul += Qsticking2(myrack.getRackTiles(), moves[i], qPos, zPos);
			}
			if (moveHasLetter2(moves[i], 'Q'))
			{
				cout << "MIN" << optm << " " << pess << endl;
				mul += QVAL;
			}
			if (moveHasLetter2(moves[i], 'Z'))
			{
				mul += ZVAL;
			}
			if (moveHasLetter2(moves[i], 'J'))
			{
				mul += JVAL;
			}
			optm += mul;
			pess += mul;
			//if (moveHasQ(moves[i]))
			//{
			//	//cout <<"MIN"<< optm << " " << pess<<endl;
			//	optm *= HASQVAL;
			//	pess *= HASQVAL;

			//}
			//else if (moveHasZ(moves[i]))
			//{
			//	optm *= HASZVAL;
			//	pess *= HASZVAL;
			//}
			//else if (qPos.size() != 0)
			//{
			//	int val = Qsticking(moves[i], qPos, zPos);
			//	optm *= val;
			//	pess *= val;

			//}
			BStarNode tempnode(optm, pess,moveScore, id++, moves[i]);
			cachevector.push_back(tempnode);
			if (optm < minOptm)
			{
				minaltern = minOptm;
				minOptm = optm;
				alternBStarNodeindex = bestBStarNodeindex;
				bestBStarNodeindex = (int) cachevector.size() - 1;
			}
			else if (optm == minOptm)
			{
				if (pess < cachevector[bestBStarNodeindex].pess)// check smaller range
					bestBStarNodeindex = (int) cachevector.size() - 1;
			}
			else if (optm < minaltern) {//altern node
				minaltern = optm;
				alternBStarNodeindex = (int) cachevector.size() - 1;
			}

		}
	}
	if (bestBStarNodeindex != -1)
		bestFirstAndSecond.push_back(&cachevector[bestBStarNodeindex]);
	if (alternBStarNodeindex != -1)
		bestFirstAndSecond.push_back(&cachevector[alternBStarNodeindex]);
	return &cachevector;
}
BStarNode EndSimulation::BStar(BStarNode &node, int depth, bool maximizingPlayer,Rack myrack,Rack oprack)
{
	while (maximizingPlayer)
	{
		vector<BStarNode>* branches;
		BStarNode*highestOptmWithSmalledRange=NULL;
		vector<BStarNode *> bestFirstAndSecond;
		branches = getChildren(node, myrack,oprack,true,bestFirstAndSecond);
		if ((*branches).empty())//node has no chilren
		{
				//cout << "Max: branch is empty\n";
				node.closed = true;
				return BStarNode();
		}
		else if (bestFirstAndSecond.empty() )
		{
			//cout << "Max: best is empty\n";
			if (depth == 0)//all root children are closed without terminating condition met
			{
				return (*branches)[getBestMove(*branches)];
			}
			else {
				node.closed = true;
				return BStarNode();//backup as all children are closed
			}
		}
		/*cout << "Max node: " << node.id << "\t depth: " << depth << "\t bestNode score(" << bestFirstAndSecond[0]->optm << "," <<
			bestFirstAndSecond[0]->pess << ")";
		if (bestFirstAndSecond.size() > 1)
			cout << "\t altern score(" << bestFirstAndSecond[1]->optm << ", " << bestFirstAndSecond[1]->pess << ")";
		cout << endl;*/
		
		double maxOptimisticValue = bestFirstAndSecond[0]->optm;  //max perssimistic value
		double maxPessimisticValue = getMaxPessimistic(*branches);//bestPessimisticCache[node.id]; //max perssimistic value
		if (maxOptimisticValue < node.pess || maxPessimisticValue > node.optm)
		{
			//backup
			node.pess = maxOptimisticValue;
			node.optm = maxPessimisticValue;
			//cout << "backup. " << node.optm << "," << node.pess<<endl;
			if (depth > 0)
				return BStarNode(); //TODO what to return
			//else depth=0
			if (bestFirstAndSecond.size() == 1 || bestFirstAndSecond[0]->pess >= bestFirstAndSecond[1]->optm) //terminating condition
				return *bestFirstAndSecond[0];
		}
		
			Rack newrack = myrack;
			newrack.commitMove(&(bestFirstAndSecond[0]->move));
			board->commitMove(bestFirstAndSecond[0]->move);
			board->computeCrossSets(MG->root);
			int id = BStar(*bestFirstAndSecond[0], depth + 1, false, newrack, oprack).id;
			board->uncommitMove(bestFirstAndSecond[0]->move);
			board->computeCrossSets( MG->root);
	}
	while (!maximizingPlayer)//min always starts in depth 1 (not working if min is depth 0
	{
		vector<BStarNode>* branches;
		vector<BStarNode *> bestFirstAndSecond;
		
		branches = getChildren(node, myrack,oprack,false, bestFirstAndSecond);
		if ((*branches).empty())
		{
				node.closed = true;
				return BStarNode(); 
		}
		else if (bestFirstAndSecond.empty())
		{
			if (depth == 0)//all root children are closed without terminating condition met
			{
				return (*branches)[getBestMove(*branches)];
			}
			else {
				node.closed = true;
				return BStarNode();//backup as all children are closed
			}
		}
		/*cout << "Min node: " << node.id << "\t depth: " << depth << "\t bestNode score(" << bestFirstAndSecond[0]->optm << "," <<
			bestFirstAndSecond[0]->pess << ")";
		if (bestFirstAndSecond.size() > 1)
			cout << "\t altern score(" << bestFirstAndSecond[1]->optm << ", " << bestFirstAndSecond[1]->pess << ")";
		cout << endl;*/
		
		double maxOptimisticValue = bestFirstAndSecond[0]->optm;	  //max perssimistic value
		double maxPessimisticValue = getBestPessimisticMin(*branches);//bestPessimisticCache[node.id]; //max perssimistic value

		if (maxOptimisticValue > node.pess || maxPessimisticValue < node.optm)
		{
			//backup
			node.pess = maxOptimisticValue;
			node.optm = maxPessimisticValue;
			if (depth > 0)
				return BStarNode(); //TODO what to return
			if (bestFirstAndSecond.size() == 1 || bestFirstAndSecond[0]->pess <= bestFirstAndSecond[1]->optm)
				return *bestFirstAndSecond[0];
		}
		
			Rack newrack = oprack;
			newrack.commitMove(&bestFirstAndSecond[0]->move);
			board->commitMove(bestFirstAndSecond[0]->move);
			board->computeCrossSets( MG->root);
			int id = BStar(*bestFirstAndSecond[0], depth + 1, true, myrack, newrack).id;
			board->uncommitMove(bestFirstAndSecond[0]->move);
			board->computeCrossSets(MG->root);
		
	}
	return BStarNode();
}
Move EndSimulation::start()
{
	cache.clear();
	
	EndSimulation::id = 0;
	BStarNode root(-1000, 1000, 0, 0, Move());
	BStarNode node=BStar(root, 0, true, myRack, opponetRack);
	cout << "score: " << node.score << ", optm: " << node.optm << " , pess: " << node.pess << endl;
	return node.move;
}
void EndSimulation::estimateOPRack()
{
	string boardLetters = board->getBoardLetters();
	vector<char> myLetters = myRack.getRackTiles();

	unordered_map<char, int> freq;
	freq['A'] = tileLookup->getFrequency('A');
	freq['B'] = tileLookup->getFrequency('B');
	freq['C'] = tileLookup->getFrequency('C');
	freq['D'] = tileLookup->getFrequency('D');
	freq['E'] = tileLookup->getFrequency('E');
	freq['F'] = tileLookup->getFrequency('F');
	freq['G'] = tileLookup->getFrequency('G');
	freq['H'] = tileLookup->getFrequency('H');
	freq['I'] = tileLookup->getFrequency('I');
	freq['J'] = tileLookup->getFrequency('J');
	freq['K'] = tileLookup->getFrequency('K');
	freq['L'] = tileLookup->getFrequency('L');
	freq['M'] = tileLookup->getFrequency('M');
	freq['N'] = tileLookup->getFrequency('N');
	freq['O'] = tileLookup->getFrequency('O');
	freq['P'] = tileLookup->getFrequency('P');
	freq['Q'] = tileLookup->getFrequency('Q');
	freq['R'] = tileLookup->getFrequency('R');
	freq['S'] = tileLookup->getFrequency('S');
	freq['T'] = tileLookup->getFrequency('T');
	freq['U'] = tileLookup->getFrequency('U');
	freq['V'] = tileLookup->getFrequency('V');
	freq['W'] = tileLookup->getFrequency('W');
	freq['X'] = tileLookup->getFrequency('X');
	freq['Y'] = tileLookup->getFrequency('Y');
	freq['Z'] = tileLookup->getFrequency('Z');
	freq[BLANK_TILE] = tileLookup->getFrequency(BLANK_TILE);

	for (int i = 0; i < boardLetters.size(); i++)
	{
		freq[boardLetters[i]]--;
	}

	for (int i = 0; i < myLetters.size(); i++)
	{
		freq[myLetters[i]]--;
	}

	for (unordered_map<char, int>::iterator it = freq.begin(); it != freq.end(); ++it) {
		if (it->second != 0)
			for (size_t i = 0; i < it->second; i++)
			{
				opponetRack.addTile(it->first);
			}
	}
}
void EndSimulation::updateOPRack( Move & move)
{
	opponetRack.commitMove(&move);
}
//! for test only constructor
EndSimulation::EndSimulation(Board* board, TileLookUp*tl, Rack opponentRack, Rack myRack, Gaddag * GD, Heuristics* hr)
{
	this->scoreManager = scoreManager;
	this->opponetRack = opponentRack;
	this->myRack = myRack;
	this->tileLookup = tl;
	this->board = board; //! test implicit copy constructors
	this->MG = GD;
	this->hr = hr;
}
//! for production 
//EndSimulation::EndSimulation(const Board board, TileLookUp*tl, Rack myRack, Gaddag * GD, Heuristics* hr)
//{
//	this->scoreManager = scoreManager;
//	this->opponetRack = opponentRack;
//	this->myRack = myRack;
//	this->tileLookup = tl;
//	this->board = board; //! test implicit copy constructors
//	this->MG = GD;
//	this->hr = hr;
//	void estimateOPRack();
//
//}
EndSimulation::~EndSimulation()
{
}