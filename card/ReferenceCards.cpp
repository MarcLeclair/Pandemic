#include "ReferenceCards.h"

ReferenceCards::ReferenceCards() {

	build = "BUILD A RESEARCH STATION\n"
		"Discard the city card  that matches  the city you are  in to place a research  station here";
	treat = "TREAT DISEASE\n"
		"Remove 1 disease cube from the city you are in. If this color is CURED, remove all cubes of THAT COLOR  from the city";
	share = "SHARE KNOWLEDGE\n"
		"Either: GIVE the card that MATCHES the city you are in to another player , or TAKE that card from another player.The other player must"
		"also be in the city with you";
	discover = "DISCOVE A CUBE\n"
		"At ANY research station, discard 5 city cards of the same disease color to cure that disease";
}

void ReferenceCards::displayReferences() { //display all the references for a player
	std::cout << build << std::endl;
	std::cout << treat << std::endl;
	std::cout << share << std::endl;
	std::cout << discover << std::endl;
	
}




