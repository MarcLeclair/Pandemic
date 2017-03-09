/*
/ Claudia Della Serra, 26766048
/ COMP 345, Advanced Programming with C++
/
/ Assignment 1 PlayerCard Class
*/

#pragma once
#include <string>
#include <vector>

/************************************************************************************
/ Model PlayerCard class, created for functionality of the driver program
/ Actual implementation of Player Card is the responsibility of another group member
*************************************************************************************/
class PlayerCard
{
public:
	PlayerCard();
	PlayerCard(const PlayerCard& pc);
	PlayerCard(std::string ty, std::string ttl);
	std::string getType() {
		return type;
	}

	void setType(std::string t){
		type = t;
	}

	std::string getTitle() {
		return title;
	}

	void setTitle(std::string ttl) {
		title = ttl;
	}

	~PlayerCard();

private:
	std::string type;
	std::string title;
};

const static std::vector<std::string> possibleTypes = {
	"City",
	"Event",
	"Epidemic"
};

