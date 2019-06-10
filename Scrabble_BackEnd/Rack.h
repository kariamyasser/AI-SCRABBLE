#pragma once
#include "Square.h"
#include<vector>
#include "Rack.h"
#include "move.h"
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;


class Rack
{
	enum { RACKSIZE = 7 };	//Max Size of List

public:

	vector <char> list;

	void addTile(char x);
	void removeTile(char x);
	int getSize()const;

	vector<char> getRackTiles();
	vector<char> getLeave(const Move& move)const;
	vector<char> getUniqueLeave(const Move& move)const;

	// Ahmed Soliman
	inline void eraseElementFromVector(std::vector<char> &vec, int index) {
		auto it = vec.begin() + index;
		*it = std::move(vec.back());
		vec.pop_back();
	}	// Ahmed Soliman

	// Bilal
	void commitMove(Move * move);
	// Bilal

	Rack();					    //constructor
	Rack(const Rack &R);		//copy constructor
	~Rack();				    //destructor

protected:



};