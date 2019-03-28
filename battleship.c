#include "battleship.h"
#include "util.h"

//runs battleship app
int runApp()
{
	//functions to execute various program states
	void (*fptr[])(State*) = {
		splashScreen
	};
	State state = SPLASH; //current game state

	//main game loop
	while (state != EXIT){
		(*fptr[state])(&state);
	}
	return 0;
}

void splashScreen(State* state)
{
	fprint("art/boom.txt");
	*state = EXIT;
}

