#pragma once
#include "RoleCard.h"

class RoleFactory
{
public:
	static RoleCard* create(int roleID, Map* mp) {
		switch (roleID) {
		case 0:
			return new Researcher(mp);
			break;
		case 1:
			return new Scientist(mp);
			break;
		case 2:
			return new ContingencyPlanner(mp);
			break;
		case 3:
			return new Dispatcher(mp);
			break;
		case 4:
			return new Medic(mp);
			break;
		case 5: 
			return new OperationsExpert(mp);
			break;
		case 6:
			return new QuarantineSpecialist(mp);
			break;
		}
	}
private:
	RoleFactory();
};

