#pragma once
#include "Rack.h"
#include "move.h"
#include "BagOfLetters.h"
#include "TileLookUp.h"
#include <map>
#include <algorithm>
#include <string>
#include <fstream>


class Heuristics
{
	map<string, double> double_RL;
	map<string, double> leave_DP;
	vector<pair<vector<char>, double>> SaveDP;

public:
	Heuristics();
	double getHeuristics(bool first_turn, const vector<char>& estimatedRack, const Rack & current, const Move&  move, const BagOfLetters & bag, const vector < pair<int, int>>& Qpos, const vector < pair<int, int>>& Zpos);
	double endGame(const vector<char>& estimatedRack, int currentRack_size, const Move& move, const vector<pair<int, int>>& Qpos, const  vector<pair<int, int>>& Zpos);
	double VowelCons(const vector<char>& leave);
	double SlowEndGame(int currentRack_size, int move_size);
	double preEnd(const Move& move, vector<char>  leave, const vector<char>& uniqleave);
	double midGame(bool first_turn, const Move&  move, vector<char> leave, const vector<char>& uniqleave);
	void endGame2vals(const vector<char>& estimatedRack, const Rack& current, const Move& move, const vector<pair<int, int>>& Qpos, const vector<pair<int, int>>& Zpos, double & maxVal, double & minVal);
	void ReadMap(string inDirectory);
	void Read_Leave_DP();
	void saveToFile(vector<pair<vector<char>, double>> tobesaved);
	double calculateDRL(const vector<char>& leave);
	double Double_RL(const Move& move, const vector<char>& leave, const vector<char>& uniqleave);
	double Qsticking(const vector<char>& estimatedRack, const Move& move, const vector<pair<int, int>>&  Qpos, const vector<pair<int, int>>&  Zpos);

	~Heuristics();
};




