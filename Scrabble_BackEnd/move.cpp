#include "move.h"
#include <algorithm>

bool Move::sortByFirst(const Play &a, const Play &b)
{
    return a.coordinates.first < b.coordinates.first;
}

bool Move::sortBySecond(const Play &a, const Play &b)
{
    return a.coordinates.second < b.coordinates.second;
}


void Move::sortPlaysFirst(vector<Play>&play_vector)
{
    std::sort(play_vector.begin(), play_vector.end(), sortByFirst);
    return;
}

void Move::sortPlaysSecond(vector<Play>&play_vector)
{
    std::sort(play_vector.begin(), play_vector.end(), sortBySecond);
    return;
}

vector<Play> Move::getPlaysPointer()const
{

	return this->Plays;

}

void Move::addPlay(Play play)
{
	this->Plays.push_back(play);
	this->chars.push_back(play.Letter);
	

}

void Move::addPlay(int x ,int y ,char l,bool blank)
{
	Play play(x, y, l,blank);
	this->Plays.push_back(play);
	this->chars.push_back(play.Letter);
}

void Move::setPlayPointer(vector<Play> Plays)
{
	this->Plays = Plays;
}

Move::Move()
{
	isBingo = false;
}

Move::Move(const Move& other)
{
	for (int i = 0; i < other.Plays.size(); i++)
			this->Plays.push_back(other.Plays[i]);
	this->chars = other.chars;
	isBingo = other.isBingo;
	score = other.score;
}

void Move::setBingo(bool bingo) {
	isBingo = bingo;
}
bool Move::getBingo() {
	return isBingo;
}


Move::~Move()
{
	
}
