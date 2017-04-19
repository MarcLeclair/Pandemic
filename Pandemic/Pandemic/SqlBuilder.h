#pragma once
#include "SqlConnection.h"
#include "game.h"
#include "map.h"
#include <string>


using namespace std;
#include "game.h"

Game* game; //product

class Builder
{
public:

	Game* returnGame() { return m_game; }
	virtual string* buildGame() = 0;
	void createNewStatement() { Game* game = new Game(); }
	Game* m_game;
};

class Director {

	Builder* builder;
public: 

	void setBuilder(Builder* builder) {
		this->builder = builder;
	}

	Game* getGame() { builder->returnGame(); }

	void constructStatement() {
		builder->buildGame();
	}

};






