#include "Subject.h"
#include "Observer.h"



Subject::Subject()
{
	observers = new list<Observer*>;
}


Subject::~Subject()
{
	delete observers;
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
