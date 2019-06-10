#include "ProbabilityManager.h"



double ProbabilityManager::hyperGeometricDistrubution(int population, int cluster, int specialElementsCount, int specialElementsDesired)
{
	long double distrubtion = myUtilities.C(specialElementsCount, specialElementsDesired) * myUtilities.C(population - specialElementsCount, cluster - specialElementsDesired) / myUtilities.C(population , cluster);
	return double(distrubtion);}

double ProbabilityManager::calculateRackWeight(vector<char>  opponentRack, vector<pair<char, int>> availableFrequencies)
{
	double returnValue = 1.0;
	int population = 0;
	for (int i = 0; i < availableFrequencies.size(); i++) {
		population += availableFrequencies[i].second;
	}
	if(population <7){
		return 0.0;
	}
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < availableFrequencies.size(); j++) {
			if (availableFrequencies[j].first == opponentRack[i]) {
				returnValue *= hyperGeometricDistrubution(population - i, RACK_SIZE - i, availableFrequencies[j].second, 1);
				if (returnValue<=0.0000000000001)return 0.0;
				availableFrequencies[j].second--;

			}
		}
	}
	return (returnValue);
}

ProbabilityManager::ProbabilityManager()
{

}


ProbabilityManager::~ProbabilityManager()
{
}
