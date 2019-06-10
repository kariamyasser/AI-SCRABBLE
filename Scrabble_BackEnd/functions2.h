#pragma once
#include"structs.h"
#include<vector>
#include<string>
#include<sstream>
#include<iostream>
using namespace std;

std::vector<std::string> split(const std::string &s, char delim) {
	std::stringstream ss(s);
	std::string item;
	std::vector<std::string> elems;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}


playerStart parseStart(std::string Message)
{
	playerStart Start;
	vector<string>v = split(Message, ',');
	Start.PlayerName = v[0];
	Start.connection = "ws://";
	Start.connection += v[1];
	Start.mode = v[2];
	return Start;
}

humanMove parsePlay(std::string Message)
{
	humanMove move;
	vector<string>v = split(Message, ',');
	int size = v.size();
	move.Scolumn = stoi(v[1]);
	move.Srow = stoi(v[2]);
	move.direction = stoi(v[3]);
	std::copy(v[size - 1].begin(), v[size - 1].end(), std::back_inserter(move.tiles));
	return move;
}

vector<char> getRack(std::string Message)
{
	vector<string>v = split(Message, ',');
	vector<char>tiles;
	int size = v.size();
	std::copy(v[size - 1].begin(), v[size - 1].end(), std::back_inserter(tiles));
	return tiles;
}

template<class myType>
void displayVector(vector<myType>v)
{
	for (int i = 0; i<int(v.size()); i++)
		cout << v[i] << " ";
	cout << endl;

}

vector<char> remove_char(vector<char> tiles, char delimiter)
{
	vector<char> v;
	int size = tiles.size();
	for (int i = 0; i < size; i++)
	{
		if (tiles[i] != delimiter)
			v.push_back(tiles[i]);
	}
	return v;
}
