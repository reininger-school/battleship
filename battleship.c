#include "battleship.h"
#include "util.h"

//runs battleship app
int runApp()
{
	//functions to execute various program states
	void (*stateTable[])(State*) = {
		displaySplash
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
void displaySplash(State* state)
{
	fprint("art/title.txt");
	getchar();
	*state = RULES;
}

