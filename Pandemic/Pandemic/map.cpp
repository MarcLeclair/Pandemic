// classes example
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "map.h"
using namespace std;

/*********************************
/ Default map constructor
/ Sets outbreaks and cures at 0
*************************************/
Map::Map(){
	numberOutbreaks = 0;
	for (int i = 0; i < 4; i++) {
		cured[i] = false;
		eradicated[i] = false;
	}
}

/********************************************************
/ Initial loading function
/ Used when loading a new game
/ loads all basic city information from the database
**********************************************************/
void Map::load_starting_map(){
	SqlConnection connect;
	string* select = new string("select m.cityId,m.cityName,m.cityColor, isnull(l.link1,-1) as link1, isnull(l.link2,-1) as link2, isnull(l.link3,-1) as link3, isnull(l.link4,-1) as link4, isnull(l.link5,-1) as link5, isnull(l.link6,-1) as link6, isnull(l.link7 ,-1) as link7 from Map as m INNER JOIN MapLinks as l ON m.cityId = l.cityId");

	connect.sqlExecuteSelect(select);

	vector<vector<string>> results = connect.Connection.colData;

	for (vector<string> rows : results)
	{
		int cityId = stoi(rows.at(0));
		string name = rows.at(1);
		char *color = new char[rows.at(2).length() - 1];
		strcpy(color, rows.at(2).c_str());
		int infectionCounter[4] = { 0,0,0,0 };
		bool startFresh = false;

		City* newCity = new City(cityId, name, color,infectionCounter, startFresh);

		for (int count = 3; count <= 9; count++) {
			if (stoi(rows.at(count)) != -1) {
				newCity->add_connection(stoi(rows.at(count)));

			}

		}
		citylist.push_back(newCity);
	}
  createLinks();
}

/********************************************************************************************************************
/ Function to load a previously saved map
/ Parses the city and map information from the database for a previously saved map and loads it to the current game

**********************************************************************************************************************/
void Map::load_map(){
	SqlConnection connect, iterate;
	string *select = new string("select m.cityId, m.CityName, m.cityColor, s.pawnOrNot as pawn,s.blackCube as blackCube, s.redCube as redCube, s.blueCube as blueCube, s.yellowCube as yellowCube, s.researchOrNot as research, l.link1 as link1,l.link2 as link2,l.link3 as link3,l.link4 as link4,l.link5 as link5,l.link6 as link6,l.link7 as link7 from Map as m, MapLinks as l, SaveMap as s WHERE m.cityId = l.cityId  AND m.cityId = s.cityId");

	connect.sqlExecuteSelect(select);
     
	vector<vector<string>> results = connect.Connection.colData;
	
	for (vector<string> rows : results) {
		int id = stoi(rows.at(0));
		int infectionCounter[4] = { 0,0,0,0 };
		string name = rows.at(1);
		char *color = new char[rows.at(2).length() - 1];
		strcpy(color, rows.at(2).c_str());
		bool researchCenter = false;

		for (int count = 4; count <= 7; count++) {
			infectionCounter[count - 4] = stoi(rows.at(count));

		}
		if (rows.at(8) == "true") {
			researchCenter = true;
		}


		City* newCity = new City(id, name, color, infectionCounter, researchCenter);



		for (int count = 9; count <= 15; count++) {
			if (stoi(rows.at(count)) != -1) {
				newCity->add_connection(stoi(rows.at(count)));
			}

		}

		if (rows.at(3) == "true") {
			SqlConnection playerId;

			string* execute = new string("select playerId, pawnColor from SavePlayerInfo where playerLoc = ");
			execute->append(rows.at(0));
			playerId.sqlExecuteSelect(execute);
			vector<vector<string>> playerSets = playerId.Connection.colData;

			for (vector<string> row : playerSets) {

				newCity->add_pawn(stoi(rows.at(0)));
			}

		}
	}
	
}


/*********************************************************************************************************
/ Function to display the current status of the map
/ Will output the number of outbreaks in the map, as well as the number of cured or eradicated diseases
**********************************************************************************************************/
	void Map::display_status() {
		bool nothingCured = true;
		cout << "Number of outbreaks: " << numberOutbreaks << endl;
		for (int i = 0; i < 4; i++) {
			if (cured[i]) {
				nothingCured = false;
				if (eradicated[i]) {
					switch (i) {
					case 0:
						cout << "The black disease is eradicated!" << endl;
						break;
					case 1:
						cout << "The red disease is eradicated!" << endl;
						break;
					case 2:
						cout << "The blue disease is eradicated!" << endl;
						break;
					case 3:
						cout << "The yellow disease is eradicated!" << endl;
						break;
					}
				}
				else {
					switch (i) {
					case 0:
						cout << "The black disease is cured!" << endl;
						break;
					case 1:
						cout << "The red disease is cured!" << endl;
						break;
					case 2:
						cout << "The blue disease is cured!" << endl;
						break;
					case 3:
						cout << "The yellow disease is cured!" << endl;
						break;
					}

				}
			}

		}

		if (nothingCured) {
			cout << "No dieases have been cured or eradicated" << endl;
		}
	}

/*
  


*/

/**********************************************************************
/ Function to save the map's current state to the database
/ Will save the state of the map, plus all of the cities in the map
***********************************************************************/
void Map::save_map(){
  
	SqlConnection connect;
  string *select = new string("INSERT into SaveMap(cityId, pawnOrNot,researchOrNot, blackCube, redCube,blueCube,yellowCube) VALUES");
  vector<string> mapToSave;
  //For each city in the city list, save the city's id, name, and all connections
  for (int cityIndex = 0; cityIndex < citylist.size(); cityIndex++) {
	  int id = citylist[cityIndex]->id;
	  string infectionCounter = ",";
	  bool pawnorNot = false;
	  bool researchOrNot = false;
	  //save the state of the infection counters
	  for (int infection = 0; infection < 3; infection++) {
		  infectionCounter = infectionCounter + to_string(citylist.at(cityIndex)->infectionCounters[infection]) + infectionCounter;
	  }
	  if (citylist[cityIndex]->pawnList.size() >= 1) {
		  pawnorNot = true;
	  }

	  //save the research center state
	  if (citylist[cityIndex]->researchCenter == true) {
		  researchOrNot = true;
	  }
	  string comma = std::string(" , ");
	  string cityToSave = to_string(id) +  comma + to_string(pawnorNot) + infectionCounter + to_string(researchOrNot);

	  mapToSave.push_back(cityToSave);

	  for (string str : mapToSave) {
		  if ((str) != mapToSave.back()) {
			  select->append("( " + str + " ),");
		  }
		  else
			  select->append("( " + str + " )");
	  }

	  
  }
  connect.sqlExecuteSelect(select);
}

/*********************************************************************
/ Function to add a research station to a city given that city's id
**********************************************************************/
void Map::addResearchStation(int cityId) {
	citylist[cityId - 1]->buildResearchStation();
}

/**********************************************************************
/ Function to display all cities that currently have research stations
***********************************************************************/
void Map::display_research_cities() {
	for (int cityIndex = 0; cityIndex < citylist.size(); cityIndex++) {
		if (citylist[cityIndex]->hasResearchStation()) {
			citylist[cityIndex]->display_information();
		}
	}
}

/**************************************************
/ Function to display the map's state to the user
/ Displays the current state of all cities
***************************************************/
void Map::display_information() {
	for (int cityIndex = 0; cityIndex < citylist.size(); cityIndex++) {
		citylist[cityIndex]->display_information();
	}
}

/**************************************************
/ Function to create connections between cities
****************************************************/
void Map::createLinks() {
	for (int cityIndex = 0; cityIndex < citylist.size(); cityIndex++) {
		for (int connectionIndex = 0; connectionIndex < citylist[cityIndex]->connections.size(); connectionIndex++) {
			citylist[cityIndex]->connectionsRef.push_back(citylist[citylist[cityIndex]->connections[connectionIndex] - 1]);
		}
	}
}

//
//void Map::createIndexTable(){
//  for(int i=0;i<citylist.size();i++){
//    for(int j=0;j<citylist[i].connections.size();j++){
//      citylist[i].connectionsRef.push_back(&citylist[citylist[i].connections[j]]);
//    }
//  }
//}

/*****************************************************************************************
/ Function to cure a disease
/ Takes the zone that that disease represents, and uses it to cure that color of disease
******************************************************************************************/
void Map::cureDisease(char disease) {
	cured[zoneIndex[disease]] = true;
}

/**********************************************************
/ Function to treat a disease cube in a city
/ Treats a disease cube corresponding to that city's zone
***********************************************************/
void Map::treatDisease(int cityId) {
	//If the disease has been cured, remove all cubes from this city
	if (cured[zoneIndex[citylist[cityId - 1]->zone]]) {
		citylist[cityId - 1]->infectionCounters[zoneIndex[citylist[cityId - 1]->zone]] = 0;
	}
	else { //else, only remove one cube
		citylist[cityId - 1]->infectionCounters[zoneIndex[citylist[cityId - 1]->zone]]--;
	}
	checkEradication();
}

/********************************************************************************************
/ Function to treat a disease specially
/ This function allows you to specifically treat disease cubes of a certain color in a city
*********************************************************************************************/
void Map::treatDisease(int cityId, char color) {
	if (cured[zoneIndex[color]]) {
		//If the disease is cured, treate all of the disease cubes in that city
		citylist[cityId - 1]->infectionCounters[zoneIndex[color]] = 0;
	}
	else { //else, treat all disease cubes
		citylist[cityId - 1]->infectionCounters[zoneIndex[color]]--;
	}
	checkEradication();
}

/**************************************************************************************************************************************************
/ Function to infect a city with a disease cube
/ Finds the city with that id, then infects the city
/ If there are already 3 disease cubs of that color on that city, there will be an outbreak situation and the 4th disease cube will not be placed
**************************************************************************************************************************************************/
void Map::addDisease(int cityId) {
	cityId--;
	
	//orange green
	//checking for quarantine speilcalist on nearby spots
	bool ifQuarantineSpecialist = false;
	if (citylist[cityId]->pawnOnCity("green")) {
		ifQuarantineSpecialist == true;
	}
	else {
		for (int connectionIndex = 0; connectionIndex < citylist[cityId]->connections.size(); connectionIndex++) {
			if (citylist[cityId]->connectionsRef[connectionIndex]->pawnOnCity("green")) {
				ifQuarantineSpecialist == true;
				break;
			}
		}
	}

	if (!(cured[zoneIndex[citylist[cityId]->zone]] && citylist[cityId]->pawnOnCity("orange")) && !ifQuarantineSpecialist) {
		//cout << "Adding disease cube on city: " << cityId << endl;
		if (!eradicated[zoneIndex[citylist[cityId]->zone]]) {
			if (citylist[cityId]->infectionCounters[zoneIndex[citylist[cityId]->zone]] < 3) {
				citylist[cityId]->infectionCounters[zoneIndex[citylist[cityId]->zone]]++;
			}
			else if (!citylist[cityId]->outbreakHappened) {
				citylist[cityId]->outbreakHappened = true;
				cout << "Outbreak in " << citylist[cityId]->name << "!" << endl;
				numberOutbreaks++;
				for (int connectionIndex = 0; connectionIndex < citylist[cityId]->connections.size(); connectionIndex++) {
					outbreak(citylist[cityId]->connections[connectionIndex], citylist[cityId]->zone);
				}
			}
		}

		//Reset the city outbreak indicators for the next time someone needs to infect
		for (int cityIndex = 0; cityIndex < citylist.size(); cityIndex++) {
			citylist[cityIndex]->outbreakHappened = false;
		}
	}
}

bool City::pawnOnCity(string color) {
	for (int i = 0; i < pawnRefList.size(); i++){
		if (pawnRefList[i]->get_color() == color){
			return true;
		}
	}
	return false;


}

/***************************************************************************************************************************************************
/ Function representing an outbreak situation
/ In this situation, all connected cities will be infected with one infection cube of the indicated color
/ This occurs even if the infection color does not match the city's zone color
/ This is a recursive function, which meets its base case when the current city has less than 3 disease cubes of the current infection color in it
****************************************************************************************************************************************************/
void Map::outbreak(int cityId, char color) {
	cityId--;

	//If that disease has not already been eradicated, infect its connections
	if (!eradicated[zoneIndex[color]]) {
		if (citylist[cityId]->infectionCounters[zoneIndex[color]] < 3) {
			citylist[cityId]->infectionCounters[zoneIndex[color]]++;
		}
		//We might have another outbreak in this city
		else if (!citylist[cityId]->outbreakHappened) {
			citylist[cityId]->outbreakHappened = true;
			numberOutbreaks++;
			for (int connectionIndex = 0; connectionIndex < citylist[cityId]->connections.size(); connectionIndex++) {
				outbreak(citylist[cityId]->connections[connectionIndex], color);
			}
		}
	}
}

/**********************************************************
/ Check if there are any eradicated diseases on the map
***********************************************************/
void Map::checkEradication() {
	int count[4]={0,0,0,0};

	for (int cityIndex = 0; cityIndex < citylist.size(); cityIndex++) {
		for (int infectionIndex = 0; infectionIndex < 4; infectionIndex++) {
			count[infectionIndex] += citylist[cityIndex]->infectionCounters[infectionIndex];
		}
	}

	for (int infectionIndex = 0; infectionIndex < 4; infectionIndex++) {
		if (count[infectionIndex]==0 && this->cured[infectionIndex]) {
			eradicated[infectionIndex] = true;
		}
	}
}

/*******************************************************************************************
/ Function to return a pointer to a city object depending on the ID passed to the function
/ Used for checks in the role classes
********************************************************************************************/
City* Map::getCityByID(int cityId){
  return citylist[cityId-1];

}

/*************************************************
/ Function to add a pawn to the beginning city
/ In this game, all pawns begin in Castle Town
**************************************************/
void Map::addPawn(Pawn* pawn) {
	pawnlist.push_back(pawn);
	citylist[3]->pawnRefList.push_back(pawn);
	citylist[3]->pawnList.push_back(pawn->get_playerId());
	pawn->set_location(4);
	pawn->set_location_name(citylist[4]->name);
}

/*************************************************
/ Function return an array of the placed cubes
**************************************************/

vector<int> Map::placedCubes() {
	int count[4] = { 0,0,0,0 };

	for (int cityIndex = 0; cityIndex < citylist.size(); cityIndex++) {
		for (int infectionIndex = 0; infectionIndex < 4; infectionIndex++) {
			count[infectionIndex] += citylist[cityIndex]->infectionCounters[infectionIndex];
		}
	}

	vector<int> placed;
	placed.push_back(count[0]);
	placed.push_back(count[1]);
	placed.push_back(count[2]);
	placed.push_back(count[3]);
	return placed;
}
/*************************************************
/ Function returns the number of infected cubes
**************************************************/

int Map::numberInfectedCities() {
	int count = 0;

	for (int cityIndex = 0; cityIndex < citylist.size(); cityIndex++) {
		bool ifCube = false;
		for (int infectionIndex = 0; infectionIndex < 4; infectionIndex++) {
			if (citylist[cityIndex]->infectionCounters[infectionIndex]>0) {
				ifCube = true;
				break;
			}
		}
		if (ifCube) {
			count++;
		}
	}
	return count;
}

/*************************************************
/ Function returns the number of infected cubes
**************************************************/

int Map::numberInfectedCubes() {
	int count = 0;

	for (int cityIndex = 0; cityIndex < citylist.size(); cityIndex++) {
		bool ifCube = false;
		for (int infectionIndex = 0; infectionIndex < 4; infectionIndex++) {
			count += citylist[cityIndex]->infectionCounters[infectionIndex];
		}
	}
	return count;
}

/*************************************************
/ Function returns the number of infected cubes
**************************************************/

int Map::numberResearchStations() {
	int count = 0;

	for (int cityIndex = 0; cityIndex < citylist.size(); cityIndex++) {
		if (citylist[cityIndex]->hasResearchStation()) {
			count++;
		}
	}
	return count;
}
/******************************************************************************************
/ Function to move a pawn to a new city
/ The function will take a pawn's reference and insert it into the new city's pawn array
/ It will then erase that reference from the current city's pawn array
*******************************************************************************************/
void Map::movePawn(Pawn* pawn, int cityId) {
	vector <Pawn*>::iterator it3;
	//Get the reference to the pawn we want to move and remove it from the current city
	for (it3 = citylist[(pawn->get_location()) - 1]->pawnRefList.begin(); it3 != citylist[(pawn->get_location()) - 1]->pawnRefList.end(); ++it3) {
		if ((*it3)->get_playerId() == pawn->get_playerId()) {
			it3 = citylist[(pawn->get_location()) - 1]->pawnRefList.erase(it3);
			break;
		}
	}

	vector <int>::iterator it2;
	//Remove the pawn's ID from the pawn list in the current city as well
	for (it2 = citylist[(pawn->get_location()) - 1]->pawnList.begin(); it2 != citylist[(pawn->get_location()) - 1]->pawnList.end(); ++it2) {
		if ((*it2) == pawn->get_playerId()) {
			it2 = citylist[(pawn->get_location()) - 1]->pawnList.erase(it2);
			break;
		}
	}

	//Set the pawn's new ID and add him to the new city's list
	pawn->set_location(cityId);
	pawn->set_location_name(citylist[cityId - 1]->name);
	citylist[cityId - 1]->pawnRefList.push_back(pawn);
	citylist[cityId - 1]->pawnList.push_back(pawn->get_playerId());

}

/*********************************************
/ Return the all the cities held by the map
***********************************************/
vector<City*> Map::getCities() {
	return citylist;
}

/*****************************************************************************
/ Checks for the Game Over conditions
/ First, checks if the number of outbreaks has gone above 8
/ Then checks checks if all infection cubes have been used for any color
/ Should finally check if all player cards have been used up from the deck
******************************************************************************/
bool Map::checkGameOver() {
	if (numberOutbreaks >= 8) {
		return true;
	}
	int count[4] = { 0,0,0,0 };

	//Add up all infection cube numbers for all cities in the game
	for (int cityIndex= 0; cityIndex < citylist.size(); cityIndex++) {
		for (int infectionIndex = 0; infectionIndex < 4; infectionIndex++) {
			count[infectionIndex] += citylist[cityIndex]->infectionCounters[infectionIndex];
		}
	}
	//This is wrong. should be checking if all infection cubes were used.
	for (int infectionIndex = 0; infectionIndex < 4; infectionIndex++) {
		if (count[infectionIndex] == 0 >24) {
			eradicated[infectionIndex] = true;
		}
	}
	return false;
}

/*********************************************************************
/ Check for winning conditions in the game
/ The only way the game can be won is if all 4 diseases are cured
*********************************************************************/
bool Map::checkWin() {
	bool gameWon = true;
	//Iterates over all disease. If all diseases are cured, then the game has been won
	for (int diseaseIndex = 0; diseaseIndex < 4; diseaseIndex++) {
		gameWon = gameWon && cured[diseaseIndex];
	}
	return gameWon;
}

/****************************
/ City class functions
******************************/

/***********************************************
/ City default constructor
/ Instantiates arbitrary values to the variables
*************************************************/
City::City(){
	id = -1;
	zone = 'n';
	name = "no name";

	for (int i = 0; i<4; i++) {
		this->infectionCounters[i] = 0;
	}

	researchCenter = false;
	outbreakHappened = false;
}

/*******************************************************************************
/ City Constructor
/ Used when a previous game has been loaded, or when loading saved city values
********************************************************************************/
City::City (int id, string name, char* zone, int iC[], bool researchCenter ) {
  this->id = id;
  this->name = name;
  this->zone = *zone;

  for(int infectionIndex = 0; infectionIndex < 4; infectionIndex++){
	  this->infectionCounters[infectionIndex]=(int)iC[infectionIndex];
  }
  this->researchCenter=researchCenter;
  this->outbreakHappened = false;
}

/******************************************************
/ Display the information for a City
/ Includes its name, ID and the disease cubes it holds
*******************************************************/
void City::display_information(){
	 cout <<name << "(" << id << ")" << endl;
	 cout << "Color: " << zone << endl;
	 cout << "Black Cubes: "<<infectionCounters[0]<<endl;
	 cout << "Red Cubes: "<<infectionCounters[1]<<endl;
	 cout << "Blue Cubes: "<<infectionCounters[2]<<endl;
	 cout << "Yellow Cubes: "<<infectionCounters[3]<<endl;

	 cout << "Connections: ";
	 for (int connectionIndex = 0; connectionIndex < connections.size();  connectionIndex++) {
		 cout <<connections[connectionIndex]<<", ";
	 }

	 cout<< endl;
	if(researchCenter){
		cout<< "This city has a research center" <<endl;
	}

	 for(int pawnIndex = 0; pawnIndex < pawnRefList.size(); pawnIndex++){
		cout <<"Player "<<pawnRefList[pawnIndex]->get_playerId() <<"'s pawn is on this spot."<<endl;
	 }

	 cout<< endl <<endl;
}

//void City::treatDisease(char type) {
//
//
//}

/**********************************************************
/ Function to treat disease cubes in the current city
/ Treats disease cubes corresponding to the city's zone
************************************************************/
void City::treatDisease() {
	if (this->zone == 'b' && this->infectionCounters[0]>0) {
		this->infectionCounters[0]--;
	}
	if (this->zone == 'r' && this->infectionCounters[1]>0) {
		this->infectionCounters[1]--;
	}
	if (this->zone == 'u' && this->infectionCounters[2]>0) {
		this->infectionCounters[2]--;
	}
	if (this->zone == 'y' && this->infectionCounters[3]>0) {
		this->infectionCounters[3]--;
	}
}

/*******************************************************************
/ Checks to see if the city holds any disease cubes
/ Any color of disease cubes results in returning an answer of true
********************************************************************/
bool City::hasDisease(){
	//Iterate over all infection counters
	for(int infectionIndex = 0; infectionIndex < 4; infectionIndex++){
		if(infectionCounters[infectionIndex] > 0){
			return true;
		}
	}
	return false;
}

/********************************************************************
 Function that checks for a disease of a specific type in the city
*********************************************************************/
bool City::hasDisease(char disease){
	if (infectionCounters[zoneIndex[disease]] > 0)
		return true;
  return false;
}

/******************************************************************
/ Function that checks whether this city Connects to another city
******************************************************************/
bool City::connectsTo(int newCityId){
  for(int i=0; i<connections.size();i++){
	  if(connections[i]==newCityId){
		return true;
	  }
  }
  return false;
}