#include "battleship.h"
#include "util.h"

//runs battleship app
int runApp()
{
	//functions to execute various program states
	void (*stateTable[])(State*) = {
		displaySplash, displayRules
	};
	State state = SPLASH; //current game state

	//main game loop
	while (state != EXIT){
		(*stateTable[state])(&state);
	}
	return 0;
}

//prints title splash screen and waits for enter press
//postconditions: state is set to RULES
void displaySplash(State *state)
{
	clear();
	fprint("art/title.txt");
	getchar();
	*state = RULES;
}

//print rules and waits for enter press
void displayRules(State *state)
{
	clear();
	fprint("text/rules.txt");
	getchar();
	*state = SETUP;
}
