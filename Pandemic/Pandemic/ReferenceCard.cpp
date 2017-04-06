#include "ReferenceCard.h"
#include <string>
#include <vector>
#include <iostream>


ReferenceCard::ReferenceCard() {}
ReferenceCard::~ReferenceCard() {}

/*********************************************************************
/ Function to output the titles of all Actions the Player can execute
*********************************************************************/
void ReferenceCard::outputActions() {
	for (int i = 0; i < allActions.size(); i++) {
		cout << i << ". " << allActions[i] << endl;
	}
}