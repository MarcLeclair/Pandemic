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
int Pawn::get_playerId(){
  return this->playerId;
}

void Pawn::display_information(){
  cout << "This is a "<<this->colour <<" pawn!" << endl;
}
void Pawn::set_location(int locationId){
  this->locationId=locationId;
}

//Role Card
Role::Role(string roleName){
  this->roleName=roleName;
}

void Role::display_information(){
  cout << "This is a "<<this->roleName <<" role card!" << endl;
}

//Reference Card
ReferenceCard::ReferenceCard(string info){
  this->info=info;
}

void ReferenceCard::display_information(){
  cout << "This is a "<<info<<" reference card!" << endl;
}

//Player Cards
PlayerCard::PlayerCard(string type){
  this->type=type;
}

void PlayerCard::display_information(){
  cout << "This is a "<<this->type <<" PlayerCard!" << endl;
}

/*
int main () {
	vector<Possession*> possessions;
  possessions.push_back(new Possession());
  possessions.push_back(new Pawn("Red"));
  possessions.push_back(new Role("Medic"));
  possessions.push_back(new ReferenceCard("Basic Action"));
  possessions.push_back(new PlayerCard("Bridge of Eldin"));
  possessions.push_back(new PlayerCard("Faron Spring"));
  for(int i=0; i < possessions.size(); i++){
    possessions[i]->display_information();
  }


	return 0;
}*/
