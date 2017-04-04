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
	Subject(const Subject& sub);
	const Subject& operator=(const Subject& sub);
	virtual ~Subject();
private:
	list<Observer*> *observers;
};

