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

    void set_location(int);
	void set_player_id(int);
	int get_location();
    int get_playerId();
    void display_information();
	string get_color();
 
};

#endif

