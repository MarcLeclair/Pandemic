#include "togglePlayerStats.h"

togglePlayerStats::togglePlayerStats()
{

};

void togglePlayerStats::getStats(Player* p) {
	if (p->getViewPlayer() == true) {
		togglePlayerStats *PS = new basicStats;

		if (p->getViewPAction() == true) {

		}

		if (p->getViewDrawCard() == true) {
			PS = new drawPlayerCard(PS);
		}

		if (p->getViewDrawInfection() == true) {
			PS = new drawInfection(PS);
		}

		cout << PS->getGameLog(p) << endl;
	}
	
}