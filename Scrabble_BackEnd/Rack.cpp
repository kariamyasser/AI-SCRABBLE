#include "Rack.h"


Rack::Rack()
{
	list.reserve(7);

}

Rack::Rack(const Rack & R)
{
	this->list.reserve(7);
	this->list = R.list;
}

vector<char> Rack::getLeave(const Move& move)const
{
	// vector<Play> plays = move.Plays;
	vector<char> leave = this->list;
	int size = move.Plays.size();

	for (int i = 0; i < size; i++) {
		if (move.Plays[i].Blank == true) {
			std::vector<char>::iterator position = std::find(leave.begin(), leave.end(), BLANK_TILE);
			if (position != leave.end()) // == myVector.end() means the element was not found
				leave.erase(position);
		}
		else {
			std::vector<char>::iterator position = std::find(leave.begin(), leave.end(), move.Plays[i].Letter);
			if (position != leave.end()) // == myVector.end() means the element was not found
				leave.erase(position);
		}
		
	} 		// eraseElementFromVector now uses index not value or iterator so USED std::Find instead to get iterator and used erase

	return leave;
}

void Rack::commitMove(Move * move)
{
	int size = move->Plays.size();
	for (int i = 0; i < size; i++) {
		if (move->Plays[i].Blank == true) {
			std::vector<char>::iterator position = std::find(this->list.begin(), this->list.end(), BLANK_TILE);
			if (position != this->list.end()) // == myVector.end() means the element was not found
				this->list.erase(position);
		}
		else
		{
			std::vector<char>::iterator position = std::find(this->list.begin(), this->list.end(), move->Plays[i].Letter);
			if (position != this->list.end()) // == myVector.end() means the element was not found
				this->list.erase(position);
		}
	
		// eraseElementFromVector now uses index not value or iterator so USED std::Find instead to get iterator and used erase
	}
}



vector<char> Rack::getUniqueLeave(const Move& move) const
{

	vector<char> leave = getLeave(move);


	for (int i = 0; i < leave.size(); i++)
	{
		for (int k = i + 1; k < leave.size(); k++)
		{
			if (leave[i] == leave[k])
				leave.erase(leave.begin() + k);
		}
	}

	return leave;

}


void Rack::addTile(char x)
{
	if (list.size() == 7)
		return;

	list.push_back(x);

}

vector<char> Rack::getRackTiles()
{
	return list;
}

void Rack::removeTile(char x)
{

	for (int i = 0; i < list.size(); i++)
	{
		if (list[i] == x)
		{

			list.erase(list.begin() + i);

			break;
		}
	}

}


int Rack::getSize()const
{
	return list.size();
}



Rack::~Rack()
{
}