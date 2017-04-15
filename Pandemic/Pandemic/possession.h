#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <functional>


#ifndef POSSESSION_H
#define POSSESSION_H
using namespace std;
class Possession {
	string title;
};
class Pawn : public Possession {
	string colour;
	int locationId;
	int playerId;
	string locationName;
public:
	Pawn(string, int);
	Pawn();
	Pawn(const Pawn&);

	void set_location(int locationId) { this->locationId = locationId; }
	void set_player_id(int pid) { this->playerId = pid; }
	void set_location_name(string name) { this->locationName = name; }
	int get_location() { return this->locationId; }
	int get_playerId() { return this->playerId; }
	string get_location_name() { return this->locationName; }
	void display_information();
	string get_color() { return this->colour; }

};

#endif