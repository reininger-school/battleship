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
	srand(time(NULL));
	//initialize players
	//place computer ships
	//choose who goes first
}

//initialize player data
void initializePlayer(Player *player)
{
	initializeBoard(player->board);
	initializeShips(player->ships);
	initializeStats(&player->stats);
}

//set all board tiles to water
void initializeBoard(Tile board[ROWS][COLUMNS])
{
	for (int i=0; i<ROWS; i++){
		for (int j=0; j<COLUMNS; j++){
			board[i][j].entity = WATER;
			board[i][j].visible = WATER_CHAR;
		}
	}
}

//size of array must be at least 5
void initializeShips(Ship ships[])
{
	//set all ships to unsunk
	for (int i=0; i<N_SHIPS; i++){
		ships[i].sunk = 0;
	}
	//carrier
	ships[CARRIER].symbol = 'C';
	ships[CARRIER].size = ships[CARRIER].hp = 5;
	//battleship
	ships[BATTLESHIP].symbol = 'B';
	ships[BATTLESHIP].size = ships[BATTLESHIP].hp = 4;
	//cruiser
	ships[CRUISER].symbol = 'R';
	ships[CRUISER].size = ships[CRUISER].hp = 3;
	//submarine
	ships[SUBMARINE].symbol = 'S';
	ships[SUBMARINE].size = ships[SUBMARINE].hp = 3;
	//destroyer
	ships[DESTROYER].symbol = 'D';
	ships[DESTROYER].size = ships[DESTROYER].hp = 2;
}

void initializeStats(Stats *stats)
{
	stats->total_hits = stats->total_misses = stats->hm_ratio = 0;
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
