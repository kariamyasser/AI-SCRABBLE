#pragma once
#include "Play.h"
#include<vector>
class Move
{
	
public:
	vector<Play>  Plays;
	vector<char> chars;
	bool isBingo;
	int score;
	vector<Play> getPlaysPointer() const;
	void setBingo(bool bingo);
	bool getBingo();
	void addPlay(Play play);
	void addPlay(int x, int y, char l, bool blank = false);
	void  setPlayPointer(vector<Play> Plays);

    // sorting a vector of plays
    // used for sortPlays
    static bool sortByFirst(const Play &a, const Play &b);
    static bool sortBySecond(const Play &a, const Play &b);

    static void sortPlaysFirst(vector<Play>&play_vector);
    static void sortPlaysSecond(vector<Play>&play_vector);

	Move();
	Move(const Move& other);
	~Move();
};

