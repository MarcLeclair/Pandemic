/********************************************************************
/ This class is a concrete implementation of an observer on a Game
/ GameStatistics objects will be updated whenever the  object that
/ they observe notifies them of an update.
/ They hold a single Game object to which they observe
/ Thus, each Game should have its own observer attached.
*********************************************************************/


#pragma once
#include "Observer.h"
#include "Game.h"

class GameStatistics : public Observer
{
public:
	GameStatistics();
	GameStatistics(Game* pl);
	GameStatistics(const GameStatistics& pv);
	const GameStatistics& operator=(const GameStatistics& pv);
	~GameStatistics();
	void update();
	void displayGame();
	Game* getGame();
private:
	Game* game;
};

/**
* Abstract decorator class - note that it extends the Observer abstract class
*/
class ObserverDecorator : public Observer {
protected:
	Observer *decoratedObserver;
	Game *game;
public:
	/**
	* Wraps a Observer object inside an object of one of
	* ObserverDecorator's subclasses
	*/
	ObserverDecorator(Observer *decoratedObserver, Game *game) {
		this->decoratedObserver = decoratedObserver;
		this->game = game;
	}
	/**
	* Provides the wrapper with the Observer interface and delegates
	* its methods to the wrapped Observer object.
	*/

	void update() {
		this->decoratedObserver->update();
	}
};

/** Decorator that mixes Milk with Observer.
* It is a subclass of ObserverDecorator, and thus a subclass of Observer.
*/
class CitiesStatistics : public ObserverDecorator {
public:
	/**
	* When creating a decorated Observer, pass a Observer to be decorated
	* as a parameter. Note that this can be an already-decorated Observer.
	*/
	CitiesStatistics(Observer *decoratedObserver, Game *game) : ObserverDecorator(decoratedObserver,game) {}
	/**
	* Overriding methods defined in the abstract superclass.
	* Enables to provide different behavior for decorated Observer methods
	*/
	void update() {
		ObserverDecorator::update();
		int number = this->game->getMap()->numberInfectedCities();
		cout << "Cities Statistics:" << endl;
		cout << "Number of cities infected: " << number << endl << endl;
	}

};

class PlayersStatistics : public ObserverDecorator {
public:
	/**
	* When creating a decorated Observer, pass a Observer to be decorated
	* as a parameter. Note that this can be an already-decorated Observer.
	*/
	PlayersStatistics(Observer *decoratedObserver, Game *game) : ObserverDecorator(decoratedObserver, game) {}
	/**
	* Overriding methods defined in the abstract superclass.
	* Enables to provide different behavior for decorated Observer methods
	*/
	void update() {
		ObserverDecorator::update();
		vector<Player*> playerlist = this->game->getPlayerlist();
		cout << "Player Statistics:" << endl;
		for (int i = 0; i < playerlist.size(); i++) {
			cout << "Player " << playerlist[i]->getPlayerID() << " has "<< playerlist[i]->getNumOfCards() <<" cards in hand"<<endl;
		}
		cout << endl;
	}

};

class DiseaseStatistics : public ObserverDecorator {
public:
	/**
	* When creating a decorated Observer, pass a Observer to be decorated
	* as a parameter. Note that this can be an already-decorated Observer.
	*/
	DiseaseStatistics(Observer *decoratedObserver, Game *game) : ObserverDecorator(decoratedObserver, game) {}
	/**
	* Overriding methods defined in the abstract superclass.
	* Enables to provide different behavior for decorated Observer methods
	*/
	void update() {
		ObserverDecorator::update();
		int number = this->game->getMap()->numberInfectedCubes();
		cout << "Disease Statistics:" << endl;
		cout << "Number of infection cubes found on the map: " << number << endl << endl;;
	}

};

class ResourcesStatistics : public ObserverDecorator {
public:
	/**
	* When creating a decorated Observer, pass a Observer to be decorated
	* as a parameter. Note that this can be an already-decorated Observer.
	*/
	ResourcesStatistics(Observer *decoratedObserver, Game *game) : ObserverDecorator(decoratedObserver, game) {}
	/**
	* Overriding methods defined in the abstract superclass.
	* Enables to provide different behavior for decorated Observer methods
	*/
	void update() {
		ObserverDecorator::update();
		auto infectionCounters = game->getMap()->placedCubes();

		int remainingResearchStations = 6- game->getMap()->numberResearchStations();
		int infectionCountersBlack = 24 - infectionCounters[0];
		int infectionCountersRed = 24 - infectionCounters[1];
		int infectionCountersBlue = 24 - infectionCounters[2];
		int infectionCountersYellow = 24 - infectionCounters[3];

		cout << "ResourcesStatistics:" << endl;
		cout << "Number of research stations left in supply : " << remainingResearchStations << endl;
		cout << "Number of Black Cubes  left in supply: " << infectionCountersBlack << endl;
		cout << "Number of Red Cubes left in supply: " << infectionCountersRed << endl;
		cout << "Number of Blue Cubes left in supply: " << infectionCountersBlue << endl;
		cout << "Number of Yellow Cubes left in supply: " << infectionCountersYellow << endl << endl;
	}

};