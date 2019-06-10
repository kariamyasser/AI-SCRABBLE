#include "BStar.h"
#include <limits>
#include "Play.h"
#include "move.h"
#include <vector>
#include "Board.h"
#include <algorithm>
//BStar::BStar(Square board[ROWS_COUNT][COLUMNS_COUNT])
//{
//
//}
int  minimax(Board board, int depth, int alpha, int beta, bool maximizingPlayer)
{
	return 0;
	////TODO: how to calc score?
	//if (depth == 0 /*TODO:|| game over in position*/)
	//	return 0;

	//if (maximizingPlayer)
	//{
	//	int maxEval = INT_MIN;
	//	vector<Move> moves;//=getPlays()
	//	for (size_t i = 0; i < moves.size(); i++)
	//	{
	//		int eval = minimax(board.commitMoveSim(moves[i]), depth - 1, alpha, beta,false);
	//		int maxEval = max(maxEval, eval);
	//		int alpha = max(alpha, eval);
	//		if (beta <= alpha)
	//			break;
	//		return maxEval;
	//	}
	//		
	//}
	//else {

	//	int minEval = INT_MAX;
	//	vector<Move> moves;//=getPlays()
	//	for (size_t i = 0; i < moves.size(); i++)
	//	{
	//		int eval = minimax(board.commitMoveSim(moves[i]), depth - 1, alpha, beta, true);
	//		int minEval = min(minEval, eval);
	//		int beta = min(beta, eval);
	//			if (beta <= alpha)
	//				break;
	//		return minEval;
	//	}
	//}

}
// initial call
void BStar::start()
{

}


BStar::~BStar()
{
}
