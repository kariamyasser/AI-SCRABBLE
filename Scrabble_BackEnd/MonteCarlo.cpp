#include "MonteCarlo.h"




MonteCarlo::MonteCarlo(Rack * myRack, char * boardPool, ProbabilityManager *pm)
{
	this->tileLookUp = new TileLookUp();
	this->Pm = pm;
	this->myrackchars;
	myrackchars.reserve(7);
	myrackchars = myRack->getRackTiles();
	this->boardPool = boardPool;
}


void MonteCarlo::createAvaliableLetters()
{

	//cout << "MYRACK SIZE IS " << myrackchars.size();

	for (int i = 0; i < 26; i++)
	{

		std::vector<char>::iterator it = (std::find(this->myrackchars.begin(), this->myrackchars.end(), mapping[i]));
		char  a = (it == this->myrackchars.end()) ? NULL : *it;
		char * b = strchr(this->boardPool, mapping[i]);
		if (a != NULL) {
			this->tileLookUp->setFrequency(mapping[i], this->tileLookUp->getFrequency(mapping[i]) - std::count(myrackchars.begin(), myrackchars.end(), mapping[i]));

		}
		if (b != NULL) {
			this->tileLookUp->setFrequency(mapping[i], this->tileLookUp->getFrequency(mapping[i]) - std::count(boardPool, boardPool + strlen(boardPool), mapping[i]));
		}
	}
	std::vector<char>::iterator it = (std::find(this->myrackchars.begin(), this->myrackchars.end(), BLANK_TILE));
	char  a = (it == this->myrackchars.end()) ? NULL : *it;
	char * b = strchr(this->boardPool, BLANK_TILE);
	if (a != NULL) {
		this->tileLookUp->setFrequency(BLANK_TILE, this->tileLookUp->getFrequency(BLANK_TILE) - std::count(myrackchars.begin(), myrackchars.end(), BLANK_TILE));

	}
	if (b != NULL) {
		this->tileLookUp->setFrequency(BLANK_TILE, this->tileLookUp->getFrequency(BLANK_TILE) - std::count(boardPool, boardPool + strlen(boardPool), BLANK_TILE));
	}

	for (int i = 0; i < 26; i++)
	{
		if (this->tileLookUp->getFrequency(mapping[i]) > 0)
		{
			
			this->availableFrequinces.push_back(std::make_pair(mapping[i], this->tileLookUp->getFrequency(mapping[i])));
			
			while (this->tileLookUp->getFrequency(mapping[i]))
			{
				this->availableCharacters.push_back(mapping[i]);
				this->tileLookUp->setFrequency(mapping[i], this->tileLookUp->getFrequency(mapping[i]) - 1);
			}
		}
	}
	if (this->tileLookUp->getFrequency(BLANK_TILE) > 0)
	{
	//	this->availableFrequinces.push_back(std::make_pair(BLANK_TILE, this->tileLookUp->getFrequency(BLANK_TILE)));
		while (this->tileLookUp->getFrequency(BLANK_TILE))
		{
			//this->availableCharacters.push_back(BLANK_TILE);
			this->tileLookUp->setFrequency(BLANK_TILE, this->tileLookUp->getFrequency(BLANK_TILE) - 1);
		}
	}

	delete this->tileLookUp;
	delete b;


}

vector<pair<vector<char>, double>> MonteCarlo::simulation(int N)
{
	this->createAvaliableLetters();
	vector<pair<vector<char>, double>> estimatedRackCost;
	for (int i = 0; i < N; i++) {
		std::vector<char> temp = this->availableCharacters;
		std::vector<char> rackgenerated;
		cout << "THE AVAILBLE CHARACTERS SIZE :" << availableCharacters.size() << endl;
		int sizeofj = (7 > availableCharacters.size()) ? availableCharacters.size() : 7;
		for (int j = 0; j < sizeofj; j++) {
			const int range_from = 0;
			const int range_to = temp.size() - 1;
			std::random_device                  rand_dev;
			std::mt19937                        generator(rand_dev());
			std::uniform_int_distribution<int>  distr(range_from, range_to);
			int index = distr(generator);
			rackgenerated.push_back(temp[index]);
			temp.erase(temp.begin() + index);

		}
		sort(rackgenerated.begin(), rackgenerated.end());
		double value = Pm->calculateRackWeight(rackgenerated, this->availableFrequinces);
		estimatedRackCost.push_back(std::make_pair(rackgenerated, value));
		temp.clear();
		rackgenerated.clear();
	}
	return estimatedRackCost;
}

MonteCarlo::~MonteCarlo()
{
	delete this->tileLookUp;
}
