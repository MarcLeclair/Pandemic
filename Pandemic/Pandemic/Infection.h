#pragma once
#include <iostream>
using namespace std;

class Infection
{
private:
	vector<int> toInfect = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48 };
	vector<int> toInfectDiscard;
	int cubes = 0;

public:
	Infection();
	void drawInfection();
	void shuffleInfection();
	void startInfect();

	/*void startInfect() {
	int counter = 0;
	while (counter < 3) {
	getLocation(roll (0,2));
	if (getCubes() == 0) {
	cubes += 3;
	counter++;
	}
	counter++; //just to break for demo purposes
	}
	while (counter < 6) {
	getLocation(roll(0,2));
	cubes = 2;
	counter++;
	}
	while(counter < 9) {
	getLocation(roll(0,2));
	cubes = 1;
	counter++;
	}*/
}


};

