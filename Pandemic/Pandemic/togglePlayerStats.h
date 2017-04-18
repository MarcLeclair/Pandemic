#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "player.h"
#include "map.h"
#include "Observer.h"

using namespace std;

class togglePlayerStats
{
public:
	togglePlayerStats();
	virtual string getGameLog(Player* p) = 0;
	void getStats(Player* p);
};

class basicStats : public togglePlayerStats {
public:
	string getGameLog(Player* p) {
		string back = "Player" + p -> getPlayerID();
		return back + " has: /n";
	}
};

class togglePlayerDecorator : public togglePlayerStats {
protected:
	togglePlayerStats *toggledView;

public:
	togglePlayerDecorator(togglePlayerStats *toggledView) {
		this->toggledView = toggledView;
	}

	string getGameLog(Player* p) {
		return toggledView->getGameLog(p);
	}
};

class playerAction :public togglePlayerDecorator {
public:
	playerAction(togglePlayerStats *toggledView) : togglePlayerDecorator(toggledView) {}

	string getGameLog(Player* p) {
		return togglePlayerDecorator::getGameLog(p);
	}

};

class drawPlayerCard :public togglePlayerDecorator {
public:
	drawPlayerCard(togglePlayerStats *toggledView) : togglePlayerDecorator(toggledView) {}

	string getGameLog(Player* p) {
		return togglePlayerDecorator::getGameLog(p);// +p->displayCardsInHand();
	}

};

class drawInfection :public togglePlayerDecorator {
public:
	drawInfection(togglePlayerStats *toggledView) : togglePlayerDecorator(toggledView) {}

	string getGameLog(Player* p) {
		return togglePlayerDecorator::getGameLog(p);
	}

};

