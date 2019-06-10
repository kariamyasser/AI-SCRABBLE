#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include "Constants.h"
#include <intrin.h>


class GaddagNode {
public:
	static int idCounter;
	GaddagNode* children[27] = {};
	unsigned int transitions = 0;
	unsigned int end = 0;
	int ID;
	GaddagNode(char x);
	~GaddagNode();

	//GaddagNode* putTransitionChar(char transitionChar);
	GaddagNode* putTransitionChar(char transitionChar, GaddagNode * son);

	GaddagNode* getChildren(char  transitionChar);


	bool contains(std::string query);

	bool containsRecur(std::string query);

	void putEnd(char endChar);

	bool hasCharAsEnd(char endChar);

	bool contains(unsigned int x, char y);

	GaddagNode** getChildren();

	int getTransitions();

	int getEnd();

	unsigned int calculateChildrenIndex(char x);

	void getOnesPositions(unsigned int  transitions, std::vector<unsigned int>&res);


};
