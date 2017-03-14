#include <iostream>
#include <string>
#include <vector>

#include "possession.h"
#ifndef MAP_H
#define MAP_H
using namespace std;
class City {
  public:
	string name;// name of city
    int id; // id of city
    char zone; //color of city
    double location[2];// location of city 
    int infectionCounters[4]; //number of infection counters of each type
    bool researchCenter; //if city has a research station
	bool outbreakHappened; //if an outbreak happened this turn
    vector<int> pawnList; //list of pawns id
	vector<Pawn*> pawnRefList; //list of pawns reference
    vector<int> connections; //list of connected city ids
    vector<City*> connectionsRef; //list of connected city references
  public:
  	City (int,string,char,double,double,int[],bool);//id,name,zone,locationx,locationy,infection counters, if rearch station
  	City ();
    void add_connection(int); //adds a connection to a city
    void add_pawn(int); //adds pawn to a city
  	void display_information(); //displays information about the city
    void set_location (int,int); //sets location of city
    bool hasResearchStation();     //If the city has a research station or not
    int getCityID();                     //Return the city's ID
    void buildResearchStation();  //Build a research station in the current city
    bool hasDisease();//checks if a city has any disease
    bool hasDisease(char); //checks if a city has a disease of specific type
	void treatDisease(); //treats disease on city
	void treatDisease(char); //treats disease of specific color on city
    bool connectsTo(int);  //currentCity checks if it connects to a city with the ID newCity
 
};
class  Map{
	bool cured[4]; //list if a disease has been cured
	bool eradicated[4]; //list of if a disease has been eradicated
	vector<City> citylist; //list of all cites
	vector<Pawn*> pawnlist; //list of pawns
 	int width, height;
public:
	void addDisease(int);//adds a single disease cube to a specified city 
	void checkEradication(); //checks if a disease is iradicated
    void save_map(); //saves map to save file
    void load_map(); //loads map from save file
    void createIndexTable(); //deprecated
    void createLinks(); //creates pointer links between cities
    void display_information(); // displays information about all cities
    void load_starting_map(); //loads the starting map
	void display_research_cities(); //displays all cities that have research stations
	void cureDisease(char); // makes a disease as being cured
	void treatDisease(int); // tread the cities color disease on the city
	void treatDisease(int, char); //treat specified color disease at specified city
	void addPawn(Pawn*); //adds a pawn to starting location
	void movePawn(Pawn*, int); //moves a pawns location
    City getCityByID(int); //returns the city given by specified int 
    Map ();
private:
	void outbreak(int, char); //handles outbreaks
 
};


#endif

