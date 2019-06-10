#pragma once
#include"Board.h"
#include<Windows.h>
#include<iostream>
#include "Rack.h"
#include "structs.h"
class Logger
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
public:
	void DisplayBoard(Board * board);
	void DisplayRack(Rack * rack);
	void PrintMove(Move * move);
	void PrintMoveStruct(const playMove& move);


	Logger();
	~Logger();
};