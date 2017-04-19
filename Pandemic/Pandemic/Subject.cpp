#include "Subject.h"
#include "Observer.h"


/***************************************************
/ Subject default constructor
/ Instantiates an empty list of observer pointers
****************************************************/
Subject::Subject()
{
	observers = new list<Observer*>;
}

/************************************************
/ Subject copy constructor
/ constructs a copy of an existing subject
/ Most importantly is the copy of observers
/ This must be a shallow copy, for now, since
/ abstract type Observer can't be instantiated
*************************************************/
Subject::Subject(const Subject& sub) {
	observers = sub.observers;
}

/*******************************************************
/ Overloaded assignment operator
/ Deletes current references to avoid confusion before
/ copying the passed values
*******************************************************/
const Subject& Subject::operator=(const Subject& sub) {
	if (&sub != this) {
		delete observers;

		observers = sub.observers;
	}
	return *this;
}

Subject::~Subject()
{

	list<Observer*>::iterator i = observers->begin(); //returns a bidirectional iterator pointing to the first element in the list
	for (; i != observers->end(); ++i) {
		delete *i;
	}

}

/****************************************************************
/ Function to attach an observer to the subject
/ Pushes the input observer reference onto a vector of observers
*******************************************************************/
void Subject::attach(Observer* obs) {
	observers->push_back(obs);
}

/****************************************************************************
/ Function to remove an observer from the list of observers on this subject
/ This is no longer update the observer with the subject's state
*****************************************************************************/
void Subject::detach(Observer* obs) {
	observers->remove(obs);
}

/********************************************************************************************************
/ Function to iterate through the list of Observers attached to this subject and update the indicated one
/ Note: using the list container's iterator, which will go through each object in the list
/ and will stop on the one matching the object indicated in the function
**********************************************************************************************************/
void Subject::notify() {
	list<Observer*>::iterator i = observers->begin(); //returns a bidirectional iterator pointing to the first element in the list
	for (; i != observers->end(); ++i) {
		(*i)->update();
		//Update is an abstract function from Observer which will be implemented by the descendent classes of Observer
	}

}
