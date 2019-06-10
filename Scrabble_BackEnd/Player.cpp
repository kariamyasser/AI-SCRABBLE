#include "Player.h"

Player::Player(string name)
{
	playerName = name;
	playerScore = 0;
	cummulativePenalty = 0;
	rack = new Rack;
}
Player:: ~Player()
{
	delete rack;
}