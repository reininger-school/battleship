#include "battleship.h"
#include "util.h"

//initial game state
#define START_STATE SPLASH

//runs battleship app
int runApp()
{
	Player human, computer;
	State state = START_STATE; //initialize game state

	//table of functions defining state behavior
	void (*stateTable[])() = {
		displaySplash, displayRules, setupGame
	};

	//main game loop
	while (state != EXIT){
		(*stateTable[state])(&state, &human, &computer);
	}
	return 0;
}

//prints title splash screen and waits for enter press
//postconditions: state is set to RULES
void displaySplash(State *state, Player *human, Player *computer)
{
	clear();
	fprint("art/title.txt");
	getchar();
	*state = RULES;
}

//print rules and waits for enter press
//postconditions: state is set to SETUP
void displayRules(State *state, Player *human, Player *computer)
{
	clear();
	fprint("text/rules.txt");
	getchar();
	*state = SETUP;
}

//setup game
void setupGame(State *state, Player *human, Player *computer)
{
	//seed random generator
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
	//place randomly
	//place manually
}

void placeComputerShips()
{
	//place randomly
}

void placeShipsRandomly(Tile board[ROWS][COLUMNS])
{

}

//returns 0 or 1
int randomPlayer()
{
	return rand() % 2;
}

void displayPregameCutscene()
{

}
