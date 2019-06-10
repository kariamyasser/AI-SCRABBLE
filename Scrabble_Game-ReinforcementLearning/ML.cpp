#include "ML.h"



ML::ML()
{
}

void ML::Write2File(Board &board, Rack &rack, Move &m, int score, bool append)
{
	ofstream out;
	if (append) out.open("ML.txt", fstream::app);
	else out.open("ML.txt");

	//Write Board
	for (int i = 0; i < ROWS_COUNT; i++)
	{
		for (int j = 0; j < COLUMNS_COUNT; j++)
		{
			if (board.isEmptySquare(i, j))
				out << "_ ";
			else
				out << board.getLetter(i, j) << " ";
		}
	}
	out << "\n";

	//Write Rack
	vector<char> rackLetters = rack.getRackTiles();
	int size = rackLetters.size();

	if (size != 0)
	{
		for (int i = 0; i < size; i++)
			out << rackLetters[i] << " ";
	}
	else
	{
		out << "_";
	}
	out << "\n";

	//Write Move
	vector<Play> p = m.Plays;
	int playsSize = p.size();
	for (int i = 0; i < ROWS_COUNT; i++)
	{
		for (int j = 0; j < COLUMNS_COUNT; j++)
		{
			char c = '_';
			for (int k = 0; k < playsSize; k++)
			{
				pair<int, int> coord = p[k].get_Coordinates();
				if (coord.second == i && coord.first == j) c = p[k].get_Letter();
			}
			out << c << " ";
		}
	}
	out << "\n";

	//Write Score
	out << score << "\n";
	out.close();
}

ML::~ML()
{
}
