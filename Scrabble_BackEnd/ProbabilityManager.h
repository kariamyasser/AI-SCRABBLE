#pragma once
#include "TileLookUp.h"
#include "Utilities.h"
#include "Rack.h"
#include "Constants.h"
#include <vector>
using namespace std;
class ProbabilityManager
{
public:
	
	TileLookUp* tileLookup;
	Utilities myUtilities;

	double hyperGeometricDistrubution(int population, int cluster, int specialElementsCount, int specialElementsDesired);
	double calculateRackWeight(vector<char>opponentRack, vector<pair<char,int>> availableFrequencies);
	
	ProbabilityManager();
	~ProbabilityManager();
};

