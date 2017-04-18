#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "SqlConnection.h"
#include "possession.h"
#ifndef MAP_H
#define MAP_H
using namespace std;

/******************************************************************
/ City Class
/ Node class for the map (encapsulated as an inner class)
/ This class represents the cities that players can be located in
/ Cities can hold research stations and disease cubes of any color
/ Hold references to all connections that they are connected to
********************************************************************/
class City {
  public:
	  map<char, int> zoneIndex = { { 'b', 0 },{ 'r', 1 },{ 'u', 2 },{ 'y', 3 } };
	  //member variables
	  string name;// name of city
	  int id; // id of city
      char zone; //color of city
      int infectionCounters[4]; //number of infection counters of each type
	  bool researchCenter; //if city has a research station
	  bool outbreakHappened; //if an outbreak happened this turn
      vector<int> pawnList; //list of pawns id
	  vector<Pawn*> pawnRefList; //list of pawns reference
      vector<int> connections; //list of connected city ids
      vector<City*> connectionsRef; //list of connected city references


  	  City (int, string, char*, int[],bool);//id,name,zone,locationx,locationy,infection counters, if rearch station
   	  City ();
	  //getters and setters



  	  void display_information(); //displays information about the city
      bool hasDisease();//checks if a city has any disease
	  //void treatDisease(char); //treats disease of specific color on city
	  bool hasDisease(char); //checks if a city has a disease of specific type
      bool connectsTo(int);  //currentCity checks if it connects to a city with the ID newCity
	  void treatDisease(); //treats disease on city
	  bool pawnOnCity(string);
	  //Build a research station in the current city
      void buildResearchStation() {  this->researchCenter = true; }

	  //Return this city's ID
      int getCityID() {  return this->id;  }

	  // checks If the city has a research station or not
      bool hasResearchStation() {  return this->researchCenter;  }         

	  //Adds a Pawn's ID to the city's pawn id list
      void add_pawn(int pawnId) {  this->pawnList.push_back(pawnId); }

	  //Adds a connection to a city
      void add_connection(int cityID) {  this->connections.push_back(cityID);  }

};

/********************************************************************************************************************
/ Map Class
/ Holds a graph of city objects
/ Operates directly on these city objects, encapsulating them so that outside objects do not access cities directly
*********************************************************************************************************************/
class  Map{
	bool cured[4]; //list if a disease has been cured
	bool eradicated[4]; //list of if a disease has been eradicated
	vector<City*> citylist; //list of all cites
	vector<Pawn*> pawnlist; //list of pawns
 	int width, height;
	int numberOutbreaks;

public:
	map<char, int> zoneIndex = { { 'b', 0 },{ 'r', 1 },{ 'u', 2 },{ 'y', 3 } };
	void addResearchStation(int);
	void addDisease(int);//adds a single disease cube to a specified city 
	void checkEradication(); //checks if a disease is iradicated
    void save_map(); //saves map to save file
    void load_map(); //loads map from save file
    //void createIndexTable(); //deprecated
    void createLinks(); //creates pointer links between cities
    void display_information(); // displays information about all cities
	void displayCityInformation(int);// displays information about a single city
    void load_starting_map(); //loads the starting map
	void display_research_cities(); //displays all cities that have research stations
	void cureDisease(char); // marks a disease as being cured
	void treatDisease(int); // treat the cities color disease on the city
	void treatDisease(int, char); //treat specified color disease at specified city
	void addPawn(Pawn*); //adds a pawn to starting location
	void movePawn(Pawn*, int); //moves a pawns location
	void display_status(); //displays the status of the map
	void displayAdjacentCityInformation(int );
	bool checkGameOver();
	bool checkWin();
	bool hasResearchStation(int);
	bool hasDisease(int);
	bool connectsTo(int, int );
	char getZone(int);
	vector<int> getConnections(int);
	vector<int>getInfectionsCounters(int );
	vector<Pawn*> getPawnsRef(int );
	vector<int> getPawns(int);

	string getCityName(int);
	vector<int> placedCubes();
	int numberInfectedCities();
	int numberInfectedCubes();
	int numberResearchStations();
    City* getCityByID(int); //returns the city given by specified int 
	vector<City*> getCities(); // return list of cities
    Map ();
private:
	void outbreak(int, char); //handles outbreaks
};


#endif

