#pragma once
#include "sqlconnection.h"
#include "game.h"
#include "map.h"
#include <string>


using namespace std;
#include "game.h"

Game* game; //product

class builder
{
public:

	Game* returngame() { return m_game; }
	virtual void buildgame(int numOfPlayers) = 0;
	virtual void buildgame() = 0;
	void createnewstatement() { Game* game = new Game(); }
	Game* m_game;
};

class director {

	builder* m_builder;
public:

	void setbuilder(builder* bd) { m_builder = bd; }

	Game* getgame() {return m_builder->returngame(); }

	void buildLoadedGame() { m_builder->buildgame(); }
	void buildInitialGame(int number) { m_builder->buildgame(number); }
};

class loadstartgame :public builder {

	virtual void buildgame(int numOfPlayers) {
		m_game = new Game(numOfPlayers);
	}

	void buildgame() {
		//do nothing
	}
};

class loadSavedGame :public builder {

	virtual void buildgame(int numOfPlayers) {/*do nothing*/ }
	virtual void buildgame(){
		m_game = new Game();
		m_game->LoadGame();}
};






