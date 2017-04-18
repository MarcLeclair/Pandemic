#pragma once
#include <string>
#include<vector>
#include <iostream>
#include "player.h"
#include "map.h"

using namespace std;

class togglePlayerStats
{
public:
	virtual string getGameLog() = 0;
};

class togglePlayerDecorator : public togglePlayerStats {
protected:
	togglePlayerStats *toggledView;

public:
	togglePlayerDecorator(togglePlayerStats *toggledView) {
		this->toggledView = toggledView;
	}

	string getGameLog() {
		return toggledView->getGameLog();
	}
};

class playerToggle :public togglePlayerDecorator {
public:
	playerToggle(togglePlayerStats *toggledView) : togglePlayerDecorator(toggledView) {}

	string getGameLog() {
		return togglePlayerDecorator::getGameLog();
	}

};

class playerAction :public togglePlayerDecorator {
public:
	playerAction(togglePlayerStats *toggledView) : togglePlayerDecorator(toggledView) {}

	string getGameLog() {
		return togglePlayerDecorator::getGameLog();
	}

};

class drawPlayerCard :public togglePlayerDecorator {
public:
	drawPlayerCard(togglePlayerStats *toggledView) : togglePlayerDecorator(toggledView) {}

	string getGameLog() {
		return togglePlayerDecorator::getGameLog();
	}

};

class drawInfection :public togglePlayerDecorator {
public:
	drawInfection(togglePlayerStats *toggledView) : togglePlayerDecorator(toggledView) {}

	string getGameLog() {
		return togglePlayerDecorator::getGameLog();
	}

};

