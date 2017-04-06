/********************************************************************
/ This class is a concrete implementation of an observer on a Player
/ PlayerView objects will be updated whenever the Player object that
/ they observe notifies them of an update.
/ They hold a single Player object to which they observe
/ Thus, each player should have its own observer attached.
*********************************************************************/


#pragma once
#include "Observer.h"
#include "player.h"

class PlayerView : public Observer
{
public:
	PlayerView();
	PlayerView(Player* pl);
	PlayerView(const PlayerView& pv);
	const PlayerView& operator=(const PlayerView& pv);
	~PlayerView();
	void update();
	void displayPlayer();
private:
	Player* subject;
};

