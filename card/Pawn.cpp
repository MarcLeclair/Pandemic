#include "Pawn.h"

Pawn::Pawn() {

	IDcity = 1;
	bool checkForId = false;
	int possibleId = 0;
	while (!checkForId) {
		checkForId = checkIfPlayerIDexist(possibleId);
		if (checkForId == true) {
			IDplayer = possibleId;
			addPlayerIDToList(possibleId);
			break;
		}
		else {
			possibleId++;
		}
	}
};

int Pawn::getPawnID() {
	return IDplayer;
};

int Pawn::getPawnLoc() {
	return IDcity;
};

void Pawn::setPawnID(int id) {
	IDplayer = id;
};

void Pawn::setPawnLoc(int locID) {
	IDcity = locID;
};
bool Pawn::checkIfPlayerIDexist(int id) {
	for (int idInVector : listOfPlayerIDs) {
		if (id == idInVector) {
			return true;
		}
	}
	return false;
}

void Pawn::addPlayerIDToList(int id) {
	listOfPlayerIDs.push_back(id);
}
