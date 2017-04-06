#pragma once
#include <string>
#include <vector>
#include "PlayerCard.h"
#include "possession.h"
#include "map.h"

/*************************************************************************************************************
/ Class responsible for the definition of all actions players can take
/ While this gives the basic functioning of actions, some functions may be overridden in RoleCard subclasses
/ For the most part, functions defined here are inherited and untouched.
**************************************************************************************************************/
using namespace std;

class ReferenceCard
{
public:
	ReferenceCard();
	~ReferenceCard();

	vector<std::string> getAllActions() {
		return allActions;
	}

	void outputActions();



private:
	vector<string> allActions = {
		"Drive/Ferry",
		"Direct Flight",
		"Charter Flight",
		"Shuttle Flight",
		"Build Research Station",
		"Treat Disease",
		"Share Knowledge",
		"Discover Cure"
	};
};