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
  public:
  	virtual void display_information();
 
};
class Pawn: public Possession{
	string colour;
  int locationId;
  int playerId;
  public:
    Pawn (string, int);
    void set_location(int);
	int get_location();
    int get_playerId();
    void display_information();
 
};

class Role: public Possession{
  string roleName;
  public:
    Role (string);
    void display_information();
 
};

class ReferenceCard: public Possession{
  string info;
  public:
    ReferenceCard (string);
    void display_information();
 
};

//class PlayerCard: public Possession{
//  string type;
//  public:
//    PlayerCard (string);
//    void display_information();
//};


#endif

