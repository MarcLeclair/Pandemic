#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <functional>


#ifndef POSSESSION_H
#define POSSESSION_H
using namespace std;
class Possession{
	string title; 
};
class Pawn: public Possession{
	string colour;
	 int locationId;
	 int playerId;
  public:
    Pawn (string, int);
	Pawn();
	Pawn(const Pawn&);

    void set_location(int locationId) {	this->locationId = locationId;	}
	void set_player_id(int pid) { this->playerId = pid; }
	int get_location() {return this->locationId;}
    int get_playerId() {return this->playerId;}
    void display_information();
	string get_color() {	return this->colour;	}
 
};

#endif

