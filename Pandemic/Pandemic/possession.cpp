#include "possession.h"
using namespace std;

/************************************************************************************
/ Pawn constructor, sets the pawn's color and the player id to whom the pawn belongs
**************************************************************************************/
Pawn::Pawn(string colour, int playerId){
  this->colour=colour;
  this->playerId=playerId;
}

/************************************************************************
/ Default Pawn constructor to set the default values for a generic pawn
**************************************************************************/
Pawn::Pawn(){
	this->colour = "no color";
	this->playerId = 0;
}

/***************************************************
/ Copy constructor to create a deep copy of a pawn
*****************************************************/
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


/**************************************************
/ Function to display the information for a pawn
/ Displayers the pawn's color and location
***************************************************/
void Pawn::display_information(){
  cout << "This is a "<<this->colour <<" pawn!" << endl;
}
void Pawn::set_location(int locationId){
  this->locationId=locationId;
}

string Pawn::get_color() {
	return this->colour;
}

