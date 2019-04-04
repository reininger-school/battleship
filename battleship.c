#include "battleship.h"
#include "util.h"

//runs battleship app
int runApp()
{
	Player human, computer;
	State state = START_STATE; //initialize game state

	//table of functions defining state behavior
	void (* const stateTable[])() = {
		displaySplash, displayRules, setupGame, placeHumanShips,
		displayPregameCutscene
	};

	//main game loop
	while (state != EXIT){
		(*stateTable[state])(&state, &human, &computer);
	}
	return 0;
}

//print title splash screen and wait for enter
void displaySplash(State *state, Player *human, Player *computer)
{
	clear();
	fprint("art/title.txt");
	getchar();
	*state = RULES;
}

//print rules and wait for enter
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
	initializePlayer(human);
	initializePlayer(computer);
	placeComputerShips(computer);
	*state = PLACE_SHIPS;
}

//place human ships manually or randomly
void placeHumanShips(State *state, Player *human, Player *computer)
{
	promptPlacement();
	if (getIntRange(1, 2) == 1)
		placeShipsRandomly(human);
	else
		placeShipsManually(human);
	*state = CUTSCENE;
}

//prompt user to place ships randomly or manually
void promptPlacement()
{
	fprint("art/command_center.txt");
	printf("Would you like to coordinate the positions of the ships in your\n"\
		   "armada or allow your captains to position themselves?\n"\
		   "1. Place ships randomly\n"\
		   "2. Place ships manually\n");
}

void placeShipsManually(Player *player)
{
	puts("nah");
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

//set ships symbols and entities, full health
//precondition: size of array must be at least 5
void initializeShips(Ship ships[])
{
	//set all ships to unsunk
	for (int i=0; i<N_SHIPS; i++){
		ships[i].sunk = 0;
	}
	//carrier
	ships[CARRIER].symbol = 'C';
	ships[CARRIER].size = ships[CARRIER].hp = 5;
	ships[CARRIER].entity = CARRIER;
	//battleship
	ships[BATTLESHIP].symbol = 'B';
	ships[BATTLESHIP].size = ships[BATTLESHIP].hp = 4;
	ships[BATTLESHIP].entity = BATTLESHIP;
	//cruiser
	ships[CRUISER].symbol = 'R';
	ships[CRUISER].size = ships[CRUISER].hp = 3;
	ships[CRUISER].entity = CRUISER;
	//submarine
	ships[SUBMARINE].symbol = 'S';
	ships[SUBMARINE].size = ships[SUBMARINE].hp = 3;
	ships[SUBMARINE].entity = SUBMARINE;
	//destroyer
	ships[DESTROYER].symbol = 'D';
	ships[DESTROYER].size = ships[DESTROYER].hp = 2;
	ships[DESTROYER].entity = DESTROYER;
}

//set all stat fields to 0
void initializeStats(Stats *stats)
{
	stats->total_hits = stats->total_misses = stats->hm_ratio = 0;
}

//place computer ships on the board
void placeComputerShips(Player *computer)
{
	placeShipsRandomly(computer);
}

//place player ships randomly on their board
void placeShipsRandomly(Player *player)
{
	for (int i=0; i<N_SHIPS; i++){
		placeShipRandomly(player->ships[i], player->board);
	}
}

//place single ship randomly on board
int placeShipRandomly(Ship ship, Tile board[ROWS][COLUMNS])
{
	int row = 0, column = 0, dir = 0;
	do {//find open location
		row = randRange(0, ROWS);
		column = randRange(0, COLUMNS);
		dir = randRange(0, 2);
	} while(!checkShipFits(row, column, dir, ship, board));

	return placeShip(row, column, dir, ship, board);
}

//place ship on board at given position
//will always place ship does not check for other entities, does
//check out of bounds
int placeShip(int row, int column, int dir, Ship ship,
				Tile board[ROWS][COLUMNS])
{
	if (isOutOfBounds(row, column))
		return -1;
	//place on board
	if (dir == DOWN){
		for (int i=0; i<ship.size; i++){
			board[row+i][column].visible = ship.symbol;
			board[row+i][column].entity = ship.entity;
		}
	}
	else{
		for (int i=0; i<ship.size; i++){
			board[row][column+i].visible = ship.symbol;
			board[row][column+i].entity = ship.entity;
		}
	}
	return 1;
}

//returns 1 if ship fits in location on board
//checks out of bounds and non water entities
int checkShipFits(int row, int column, int dir, Ship ship, 
					Tile board[ROWS][COLUMNS])
{
	if (dir == DOWN){
		for (int i=0; i<ship.size; i++){
			if (isOutOfBounds(row+i, column) ||
				board[row+i][column].entity != WATER)
				return 0;
		}
	}
	else {
		for (int i=0; i<ship.size; i++){
			if (isOutOfBounds(row, column+i) ||
				board[row][column+i].entity != WATER)
				return 0;
		}
	}
	return 1;
}

//returns 1 if coordinate out of bounds
int isOutOfBounds(int row, int column)
{
	return (row < 0 || row >= ROWS ||
		column < 0 || column >= COLUMNS);
}

//returns 0 or 1
int randomPlayer()
{
	return randRange(0, 2);
}

void displayPregameCutscene(State *state, Player *human, Player *computer)
{
	char *str1 = "Your ships are maneuvering into position";
	char *str2 = "The first shot has been fired!!! Engaging!!!\n";

	clear();
	typewriter(str1, 30);
	typewriter("....", 900);
	printf("\n\n\n");
	fprint("art/boom.txt");
	printf("\n\n\n\n");
	typewriter(str2, 35);
	usleep(MILL_TO_MICRO(800));
	getchar();
	*state = EXIT;

	//select random player to go first
	*state = randomPlayer() ? COMPUTER_TURN : HUMAN_TURN;
}

