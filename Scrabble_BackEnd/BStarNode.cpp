#include "BStarNode.h"



BStarNode::BStarNode(double opt, double pess,double score, int id,const Move& move)
{
	this->optm = opt;
	this->pess = pess;
	this->id = id;
	this->move = move;
	this->score = score;
}

BStarNode::BStarNode()
{
	this->optm = -1;
	this->pess = -1;
	this->id = -1;
}


BStarNode::~BStarNode()
{
}
