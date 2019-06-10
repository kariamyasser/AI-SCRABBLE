#pragma once
#include "TileLookUp.h"
#include "Rack.h"
#include "ProbabilityManager.h"
#include <random>
class MonteCarlo
{
	
public:
	TileLookUp * tileLookUp;
	vector <char>  myrackchars;
	char * boardPool;
	ProbabilityManager * Pm;
	std::vector<char> availableCharacters;
	std::vector<pair<char, int>> availableFrequinces;
	MonteCarlo( Rack * myRack , char * boardPool, ProbabilityManager *pm);
	void createAvaliableLetters();
	vector<pair<vector<char>, double>> simulation(int N = 100);
	~MonteCarlo();
};

