/********************************************************************
/ Claudia Della Serra, 26766048
/ COMP 345 Assignment 2
/ NOTE: This is based on class lecture Set6, slide 18
*********************************************************************/


#pragma once
#include "Observer.h"
#include <list>

using namespace std;

/********************************************************************
/ Declaring the Subject abstract class
/ This class acts as a base class to any derived Subject classes
/ In this Distinct Part, the Player class shall be the derived class
/ This will make the Player class observable by the Observers
********************************************************************/
class Subject
{
public:
	virtual void attach(Observer* obs);
	virtual void detach(Observer* obs);
	virtual void notify();
	Subject();
	virtual ~Subject();
private:
	list<Observer*> *observers;
};

