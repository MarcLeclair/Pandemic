// classes example
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "map.h"
using namespace std;

//Map
Map::Map(){

}
void Map::load_starting_map(){
  string line;
  ifstream mapFile ("locations-and-links.csv");
  if (mapFile.is_open())
  {
    while ( getline (mapFile,line) )
    {
      vector<string> values;
      string s=line;
      int pos = 0;
      while ((pos = s.find(",")) != string::npos) {
        values.push_back(s.substr(0, pos));
        s.erase(0, pos + 1);
      }
      values.push_back(s.substr(0, pos));
      //Parses infection counters
      int infectionCounters[4];
      for(int i=0;i<7;i+=2){
        infectionCounters[i/2]=(int)values[5][i];
      }
      //Setting science centers
      bool researchCenter=false;
      if(values[6][0]=='1'){
        researchCenter=true;
      }
      //Creates New City
      City newCity=City(stoi(values[0]),values[1],values[3][0],0.0,0.0,infectionCounters,researchCenter);
      //Parses and adds connections
      s=values[2];
      while ((pos = s.find("-")) != string::npos) {
        newCity.add_connection(stoi((s.substr(0, pos))));
        s.erase(0, pos + 1);
      }
      newCity.add_connection(stoi((s.substr(0, pos))));
      //Parses and adds connections
      s=values[4];
      while ((pos = s.find("-")) != string::npos) {
        newCity.add_pawn(stoi((s.substr(0, pos))));
        s.erase(0, pos + 1);
      }
      newCity.add_pawn(stoi((s.substr(0, pos))));
      citylist.push_back(newCity);
    }
    mapFile.close();
  }

}
void Map::load_map(){
  string line;
  ifstream mapFile ("links.csv");
  if (mapFile.is_open())
  {
    while ( getline (mapFile,line) )
    {
      vector<string> values;
      string s=line;
      int pos = 0;
      while ((pos = s.find(",")) != string::npos) {
        values.push_back(s.substr(0, pos));
        s.erase(0, pos + 1);
      }
      values.push_back(s.substr(0, pos));
      //Parses infection counters
      int infectionCounters[4];
      for(int i=0;i<7;i+=2){
        infectionCounters[i/2]=(int)values[5][i];
      }
      //Setting science centers
      bool researchCenter=false;
      if(values[6][0]=='1'){
        researchCenter=true;
      }
      //Creates New City
      City newCity=City(stoi(values[0]),values[1],values[3][0],0.0,0.0,infectionCounters,researchCenter);
      //Parses and adds connections
      s=values[2];
      while ((pos = s.find("-")) != string::npos) {
        newCity.add_connection(stoi((s.substr(0, pos))));
        s.erase(0, pos + 1);
      }
      newCity.add_connection(stoi((s.substr(0, pos))));
      //Parses and adds connections
      s=values[4];
      while ((pos = s.find("-")) != string::npos) {
        newCity.add_pawn(stoi((s.substr(0, pos))));
        s.erase(0, pos + 1);
      }
      newCity.add_pawn(stoi((s.substr(0, pos))));
      citylist.push_back(newCity);
    }
    mapFile.close();
  }

}
void Map::save_map(){
  ofstream mapFile;
  mapFile.open ("links.csv",ofstream::out | ofstream::trunc);
  for(int i=0;i<citylist.size();i++){
    mapFile << citylist[i].id <<"," <<citylist[i].name<<",";
    for(int j=0;j<citylist[i].connections.size()-1;j++){
      mapFile << citylist[i].connections[j]<<"-";
    }
    mapFile << citylist[i].connections[citylist[i].connections.size()-1]<<",";
    mapFile<<citylist[i].zone<<",";
    for(int j=0;j<citylist[i].pawnList.size()-1;j++){
      mapFile << citylist[i].pawnList[j]<<"-";
    }
    mapFile << citylist[i].pawnList[citylist[i].pawnList.size()-1]<<",";
    for(int j=0;j<3;j++){
      mapFile<< citylist[i].infectionCounters[j]<<"-";
    }
    mapFile<< citylist[i].infectionCounters[3]<<",";
    if(citylist[i].researchCenter==true){
    mapFile<<"1"<<endl;
    }else{
    mapFile<<"0"<<endl;
    }

  }
  mapFile.close();


}
void Map::display_research_cities() {
	for (int i = 0; i < citylist.size(); i++) {
		if (citylist[i].hasResearchStation()) {
			citylist[i].display_information();
		}
	}
}
void Map::display_information(){
  for(int i=0;i<citylist.size();i++){
    this->citylist[i].display_information();
  }
}
void Map::createLinks(){
  for(int i=0;i<citylist.size();i++){
    for(int j=0;j<citylist[i].connections.size();j++){
      citylist[i].connectionsRef.push_back(&citylist[citylist[i].connections[j]]);
    }
  }
}
void Map::createIndexTable(){
  for(int i=0;i<citylist.size();i++){
    for(int j=0;j<citylist[i].connections.size();j++){
      citylist[i].connectionsRef.push_back(&citylist[citylist[i].connections[j]]);
    }
  }
}
City Map::getCityByID(int cityId){
  return citylist[cityId-1];

}

//City
City::City(){
}
City::City (int id, string name,char zone,double x, double y,int iC[], bool researchCenter ) {
  this->id = id;
  this->name = name;
  this->zone = zone;
  this->location[0] = x;
  this->location[1] = y;
  for(int i=0;i<4;i++){
    this->infectionCounters[i]=(int)iC[i]- '0';
  }
  this->researchCenter=researchCenter;
  
}

void City::display_information(){
 cout << "ID: " <<id << endl;
 cout << "Name: "<<name << endl;
 cout << "Location: " << location[0] <<","<< location[1] <<endl;
 cout << "# Black Cubes: "<<infectionCounters[0]<<endl;
  cout << "# Red Cubes: "<<infectionCounters[1]<<endl;
  cout << "# Blue Cubes: "<<infectionCounters[2]<<endl;
  cout << "# Yellow Cubes: "<<infectionCounters[3]<<endl;

 cout << "Connections: ";
 for(int i=0; i<connections.size();i++){
  cout <<connections[i]<<", ";
 }
 cout<< endl;
if(researchCenter){
  cout<< "This city has a research center" <<endl;
 }

 for(int i=1; i<pawnList.size();i++){
  cout <<"Player's "<<pawnList[i]<<" pawn is on this spot."<<endl;
 }

 cout<< endl <<endl;
}
void City::set_location (int x, int y) {
  location[0] = x;
  location[1] = y;
}
void City::add_connection(int x){
  this->connections.push_back(x);
}
void City::add_pawn(int pawnId){
  this->pawnList.push_back(pawnId);
}
//If the city has a research station or not
bool City::hasResearchStation(){
  return this->researchCenter;
}     
 //Return the city's ID
int City::getCityID(){
  return this->id;
}       
//Build a research station in the current city             
void City::buildResearchStation(){
  this->researchCenter=true;
}  
void City::treatDisease(char type) {


}
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
bool City::hasDisease(){
  for(int i=0;i<4;i++){
    if(infectionCounters[i]>0){
      return true;
    }
  }
  return false;
}
bool City::hasDisease(char disease){
  return false;
}
bool City::connectsTo(int newCityId){
  for(int i=0; i<connections.size();i++){
    if(connections[i]==newCityId){
      return true;
    }
  }
  return false;
}
int main () {
  string pause;

  cout <<"Press l to load Map or anything else to use default"<<endl;
  cin>>pause;

	Map map;
  if(pause=="l"){
    map.load_map();  
  }else{
    map.load_starting_map();
  }
  map.display_information();
  cout<<"Press s to save map or anything else to quit"<<endl;
  cin>>pause;
  if(pause=="s"){
    cout<<"Map Saved"<<endl;
    map.save_map();
  }

	return 0;
}
