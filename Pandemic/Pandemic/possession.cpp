// classes example

#include "possession.h"
using namespace std;

//Possesion
void Possession::display_information(){
  cout << "This is an empty possession" << endl;
}


//Pawn
Pawn::Pawn(string colour, int playerId){
  this->colour=colour;
  this->playerId=playerId;
}
Pawn::Pawn(){
	this->colour = "no color";
	this->playerId = 0;
}

Pawn::Pawn(const Pawn& copyPawn) {
	this->colour = copyPawn.colour;
	this->locationId = copyPawn.locationId;
	this->playerId = copyPawn.playerId;
}

int Pawn::get_playerId(){
  return this->playerId;
}

int Pawn::get_location() {
	return this->locationId;
}

void Pawn::display_information(){
  cout << "This is a "<<this->colour <<" pawn!" << endl;
}
void Pawn::set_location(int locationId){
  this->locationId=locationId;
}

string Pawn::get_color() {
	return this->colour;
}

