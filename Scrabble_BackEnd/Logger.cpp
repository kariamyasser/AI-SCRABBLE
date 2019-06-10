#include "Logger.h"




void Logger::DisplayBoard(Board * board) {
	cout << endl;
	for (int i = 0; i < ROWS_COUNT; i++) {

		for (int j = 0; j < COLUMNS_COUNT; j++)
		{

			// corner cases
			if ((i == 0 && j == 0) || (i == 0 && j == 14) || (i == 0 && j == 7) || (i == 7 && j == 0) || (i == 7 && j == 14)
				|| (i == 14 && j == 0) || (i == 14 && j == 7) || (i == 14 && j == 14)) SetConsoleTextAttribute(hConsole, BACKGROUND_RED);
			// diagonal cases
			else if ((i == j || i + j == 14)) {
				if ((i == 1 || i == 2 || i == 3 || i == 4 || i == 7 || i == 10 || i == 11 || i == 12 || i == 13))
					SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY);
				else if (i == 5 || i == 9) SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE);
				else if (i == 6 || i == 8) SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN);
			}
			// ran dom cses
			// 1. 2xLS
			else if (((i == 0 || 14 - i == 0) && (j == 3 || j == 11)) || (i == 7 && (j == 3 || j == 11)) || ((i == 2 || 14 - i == 2) && (j == 6 || j == 8)) || ((i == 3 || 14 - i == 3) && (j == 0 || j == 7 || j == 14)) ||
				((i == 6 || 14 - i == 6) && (j == 2 || j == 6 || j == 8 || j == 12))) SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN);
			// 2.3xLS
			else if (((i == 1 || 14 - i == 1) && (j == 5 || j == 9)) ||
				((i == 5 || 14 - i == 5) && (j == 1 || j == 5 || j == 9 || j == 13))) SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE);
			else
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			cout << " " << board->m_board[i][j].letter << " ";
		}
		cout << endl;
	}
	cout << endl;
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << " Please get me Out" << endl;
}


void Logger::DisplayRack(Rack * rack) {
	int size = rack->list.size();
	cout << size << " Tiles: ";

	for (int i = 0; i < size; ++i) {
		cout << rack->list[i] << " ";
	}
	cout << endl;
}

void Logger::PrintMove(Move * move)
{
	int size = move->Plays.size();
	cout << size << " Plays: ";
	for (int i = 0; i < size; i++) {
		cout << '(' << move->Plays[i].coordinates.first << ',' << move->Plays[i].coordinates.second << ") => " << move->Plays[i].Letter << " - ";
	}
	cout << endl;
}

void Logger::PrintMoveStruct(const playMove& move) {
	int size = move.tiles.size();
	cout << size << " Plays" << endl;
	cout << "From: (" << move.Scolumn << ',' << move.Srow << ')' << endl;
	cout << "Tiles: ";
	
	for (int i = 0; i < size; i++) {
		cout << move.tiles[i] << ' ';
	}
	if (move.direction == 0)
		cout << " Horizontal";
	else
		cout << " vertical";

	cout << endl;
	cout << "==================================" << endl;
}

Logger::Logger()
{
}

Logger::~Logger()
{
}
