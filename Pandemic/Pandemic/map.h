#include <iostream>

#include <string>
#include <vector>

#ifndef MAP_H
#define MAP_H
using namespace std;
class City {
  public:
	 string name;
    int id;
    char zone;
    double location[2];
    int infectionCounters[4];
    bool researchCenter;
    vector<int> pawnList;
    vector<int> connections;
    vector<City*> connectionsRef;
  public:
  	City (int,string,char,double,double,int[],bool);
  	City ();
    void add_connection(int);
    void add_pawn(int);
  	void display_information();
    void set_location (int,int);
    bool hasResearchStation();     //If the city has a research station or not
    int getCityID();                     //Return the city's ID
    void buildResearchStation();  //Build a research station in the current city
    bool hasDisease();
    bool hasDisease(char);
    bool connectsTo(int);  //currentCity checks if it connects to a city with the ID newCity
 
};
class  Map{
	vector<City> citylist;
 	int width, height;
public:
    void save_map();
    void load_map();
    void createIndexTable();
    void createLinks();
    void display_information();
    void load_starting_map();
	void display_research_cities();
    City getCityByID(int);
    Map ();
 
};


#endif

