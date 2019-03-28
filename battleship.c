#include "battleship.h"
#include "util.h"

//global game boards and ships
Ship humanShips[5], computerShips[5];
Tile humanBoard[10][10], computerBoard[10][10];
State state;

//runs battleship app
int runApp()
{
	//functions to execute various program states
	void (*stateTable[])() = {
		displaySplash, displayRules, setupGame
	};
	state = SPLASH; //current game state

	//main game loop
	while (state != EXIT){
		(*stateTable[state])();
	}
	return 0;
}

//prints title splash screen and waits for enter press
//postconditions: state is set to RULES
void displaySplash()
{
	clear();
	fprint("art/title.txt");
	getchar();
	state = RULES;
}

//print rules and waits for enter press
//postconditions: state is set to SETUP
void displayRules()
{
	clear();
	fprint("text/rules.txt");
	getchar();
	state = SETUP;
}

//setup game
void setupGame()
{
	//place ships
	//choose who goes first
	//pregame cutscene
}

//place human and computer ships on board
void placeShips()
{
	//place human ships
	//place computer ships
}

void placeHumanShips()
{

}
