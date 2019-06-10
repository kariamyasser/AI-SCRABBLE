#pragma once
#include <cstdint>
#include <vector>
#include <string>
#include "enums.h"

struct uTime
{
	int32_t playerTime;
	int32_t totalTime;
};
struct fromatedTime
{
	std::string playTime;
	std::string totalTime;
};
struct endMove
{
	EndReasons reason;
	int score;
	int opponentScore;
};

struct readyStruct
{

	uint8_t type;
	uint8_t order;
	std::vector<uint8_t> tiles;
	std::vector<uint8_t>board;
	int32_t score;
	int32_t opponentScore;
	int32_t playerTime;
	int32_t totalTime;
};

struct readyStruct_formated
{
	int type;
	int order;
	std::vector<char> tiles;
	char board[15][15];
	int score;
	int opponentScore;
	int playerTime;
	int totalTime;
};

struct playMove
{
	int Scolumn;
	int Srow;
	int direction;
	std::vector<char> tiles;
	int score;
};


struct player2Move
{
	uint8_t Scolumn;
	uint8_t Srow;
	uint8_t direction;
	std::vector<uint8_t> tiles;
	int32_t score;
	int32_t challengeTime;
	uTime time;
};

struct player2Move_formated
{
	int Scolumn;
	int Srow;
	int direction;
	std::vector<char> tiles;
	int score;
	std::string challengeTime;
	fromatedTime time;
};

struct playerStart
{
	std::string PlayerName;
	std::string connection;
	std::string mode;//0 agent 1 player
};

struct humanMove
{
	int Scolumn;
	int Srow;
	int direction;
	std::vector<char> tiles;
};