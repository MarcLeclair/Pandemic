#include "player.h"
using namespace std;
Player::Player(string name){
	this->name=name;
}
void Player::display_possesions(){
  cout <<"List of " <<name<<"'s possessions:" << endl;
  for(int i=0; i < possessions.size(); i++){
    possessions[i]->display_information();
  }
}

void Player::add_possession(Possession *possession){
	possessions.push_back(possession);
}
void Player::add_role(Role *role){
	this->role=role;
	possessions.push_back(role);
}
void Player::add_pawn(Pawn *pawn){
	this->pawn=pawn;
	possessions.push_back(pawn);
}

/*
int main () {
	Player playerOne = Player("Player One");
	playerOne.add_possession(new Pawn("Red"));
	playerOne.add_possession(new Role("Medic"));
	playerOne.add_possession(new ReferenceCard("Basic Action"));
	playerOne.add_possession(new PlayerCard("Bridge of Eldin"));
	playerOne.add_possession(new PlayerCard("Faron Spring"));
	playerOne.display_possesions();

	Player playerTwo = Player("Player Two");
	playerTwo.add_possession(new Pawn("Blue"));
	playerTwo.add_possession(new Role("Scientist"));
	playerTwo.add_possession(new ReferenceCard("Advance Action"));
	playerTwo.add_possession(new PlayerCard("Bridge of Eldin"));
	playerTwo.add_possession(new PlayerCard("Faron Spring"));
	playerTwo.display_possesions();

	return 0;
}*/