/*
/ Claudia Della Serra, 26766048
/ COMP 345, Advanced Programming with C++
/
/ Assignment 1 PlayerCard Class
*/

#include "PlayerCard.h"
#include <string>


PlayerCard::PlayerCard() {
	/*setType(NULL);
	setTitle(NULL);*/
}

PlayerCard::PlayerCard(std::string ty, std::string ttl)
{
	setType(ty);
	setTitle(ttl);
}

PlayerCard::PlayerCard(const PlayerCard& pc) {
	type = pc.type;
	title = pc.title;
}


PlayerCard::~PlayerCard()
{
}
