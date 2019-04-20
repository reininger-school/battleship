#include "../header/battleship.h"
#include "../header/util.h"

const char *shipNameTab[] = {"Carrier", "Battleship", "Cruiser", "Submarine",
					   		 "Destroyer"};
const char shipSymbolTab[] = {'C', 'B', 'R', 'S', 'D'};
const int shipSizeTab[] = {5, 4, 3, 3, 2};

int runApp()
{
	Player human, computer;
	State state = START_STATE; //initialize game state

	//table of functions defining state behavior
	void (* const stateTable[])() = {
		displaySplash, displayRules, setupGame, placeHumanShips,
		displayPregameCutscene, humanTurn, computerTurn
	};

	//main game loop
	while (state != EXIT){
		(*stateTable[state])(&state, &human, &computer);
	}
	return 0;
}

