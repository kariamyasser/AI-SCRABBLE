#pragma once
#include "Board.h"

class BStarNode
{

	public:
		double optm;
		double pess;
		double score;
		int id;
		Move move;//move that lead to this node from parent
		bool closed = false;
		BStarNode(double opt, double pess,double score, int id,const Move& move);
		BStarNode();
		~BStarNode();
};

