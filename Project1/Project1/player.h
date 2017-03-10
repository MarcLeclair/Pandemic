#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <functional>
#include "possession.h"

#ifndef PLAYER_H
#define PLAYER_H
using namespace std;
class Player{
	Role* role;
  	vector<Possession*> possessions;
	string name;
  public:
  	Pawn* pawn;
    Player( string);
  	void display_possesions();
  	void add_role(Role *role);
  	void add_pawn(Pawn *pawn);
    void add_possession(Possession *possession);
 
};

#endif

