#pragma once

#include <vector>
class Pawn{

	int IDcity, IDplayer;
	std::vector<int> listOfPlayerIDs;

public:
	Pawn();
	int getPawnLoc();
	int getPawnID();
	bool checkIfPlayerIDexist(int id);
private:
	void setPawnLoc(int locID);
	void setPawnID(int id);
	void addPlayerIDToList(int id);

};	