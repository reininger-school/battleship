#include "battleship.h"
#include "util.h"

//table of names for ships aligned with boardEntity enum
const char *shipNameTab[] = {"Carrier", "Battleship", "Cruiser", "Submarine",
					   		 "Destroyer"};

const char shipSymbolTab[] = {'C', 'B', 'R', 'S', 'D'};

const int shipSizeTab[] = {5, 4, 3, 3, 2};

//runs battleship app
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

//print title splash screen and wait for enter
void displaySplash(State *state, Player *human, Player *computer)
{
	clear();
	fprint("art/title.txt");
	enterToContinue();
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
	int method, confirm = 0; //1 = random placement, 2 = manual
	while (!confirm){
		clear();
		promptPlacement();
		method = getIntRange(1, 3);
		promptConfirmMethod(method);
		confirm = getYN();
	}
	if (method == 1)
		placeShipsRandomly(human, VISIBLE);
	else
		placeShipsManually(human, VISIBLE);
	*state = CUTSCENE;
}

void promptConfirmMethod(int method)
{
	if (method == 1)
		printf("You have elected to place your ships randomly. Is this"\
				"correct? (Y/n)\n");
	else
		printf("You have elected to place your ships manually. Is this"\
				"correct? (Y/n)\n");
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

void placeShipsManually(Player *player, int visible)
{
	Coord start;
	int dir, confirm = 0;
	for (int i=0; i<N_SHIPS; i++){
		while (!confirm){//prompt ship placement while position not confirmed
			displayManualInstructions(player->board);
			promptOrientation(player->ships[i]);
			dir = getRD();
			promptStartingCoord();
			start = getCoord();
			//confirm placement
			if (checkShipFits(start.row, start.column, dir, player->ships[i], player->board)){
				promptConfirmPosition(start, dir);
				confirm = getYN();
			}
			else{
				printf("Ship does not fit here.");
				enterToContinue();
			}
		}
		placeShip(start.row, start.column, dir, player->ships[i],
				  player->board, visible);
		confirm = 0;
	}
}

void promptConfirmPosition(Coord start, int dir)
{
	printf("You have selected "); 
	printCoord(start);
	char *dirStr[] = {"down", "right"};
	printf(" %s to place your ship. Is this correct? (Y/n)\n",
			dirStr[dir]);
}


void displayManualInstructions(Tile board[ROWS][COLUMNS])
{
	clear();
	fprint("art/manual_instructions.txt");
	printBoard(board);
}

void promptOrientation(Ship ship)
{
	printf("How would you like to orient your %s (%d tiles)? R (right) or"\
		   " D (down):\n", shipNameTab[ship.entity], shipSizeTab[ship.entity]);
}

void promptStartingCoord()
{
	printf("Where would you like the starting point to be?\n");
	printf("Please enter a row letter followed by column number:\n");
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
	ships[CARRIER].hp = shipSizeTab[CARRIER];
	ships[CARRIER].entity = CARRIER;
	//battleship
	ships[BATTLESHIP].hp = shipSizeTab[BATTLESHIP];
	ships[BATTLESHIP].entity = BATTLESHIP;
	//cruiser
	ships[CRUISER].hp = shipSizeTab[CRUISER];
	ships[CRUISER].entity = CRUISER;
	//submarine
	ships[SUBMARINE].hp = shipSizeTab[SUBMARINE];
	ships[SUBMARINE].entity = SUBMARINE;
	//destroyer
	ships[DESTROYER].hp = shipSizeTab[DESTROYER];
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
	placeShipsRandomly(computer, INVISIBLE);
}

//place player ships randomly on their board
void placeShipsRandomly(Player *player, int visible)
{
	for (int i=0; i<N_SHIPS; i++){
		placeShipRandomly(player->ships[i], player->board, visible);
	}
}

//place single ship randomly on board
int placeShipRandomly(Ship ship, Tile board[ROWS][COLUMNS], int visible)
{
	int row = 0, column = 0, dir = 0;
	do {//find open location
		row = randRange(0, ROWS);
		column = randRange(0, COLUMNS);
		dir = randRange(0, 2);
	} while(!checkShipFits(row, column, dir, ship, board));

	return placeShip(row, column, dir, ship, board, visible);
}

//place ship on board at given position
//will always place ship does not check for other entities, does
//check out of bounds
int placeShip(int row, int column, int dir, Ship ship,
				Tile board[ROWS][COLUMNS], int visible)
{
	if (isOutOfBounds(row, column))
		return -1;
	//place on board
	if (dir == DOWN){
		for (int i=0; i<shipSizeTab[ship.entity]; i++){
			board[row+i][column].entity = ship.entity;
			if (visible)
				board[row+i][column].visible = shipSymbolTab[ship.entity];
		}
	}
	else{
		for (int i=0; i<shipSizeTab[ship.entity]; i++){
			board[row][column+i].entity = ship.entity;
			if (visible)
				board[row][column+i].visible = shipSymbolTab[ship.entity];
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
		for (int i=0; i<shipSizeTab[ship.entity]; i++){
			if (isOutOfBounds(row+i, column) ||
				board[row+i][column].entity != WATER)
				return 0;
		}
	}
	else {
		for (int i=0; i<shipSizeTab[ship.entity]; i++){
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

//shows cutscene prior to 
void displayPregameCutscene(State *state, Player *human, Player *computer)
{
	#ifndef QUICK_START //skip cutscene
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
	#endif

	//select random player to go first
	*state = randomPlayer() ? COMPUTER_TURN : HUMAN_TURN;
}

//human turn actions
void humanTurn(State *state, Player *human, Player *computer)
{
	displayBoards(human, computer);
	//prompt where to fire
	//read coordinate
	//take shot
	//print result
	*state = EXIT;
}

//computer turn actions
void computerTurn(State *state, Player *human, Player *computer)
{
	displayBoards(human, computer);
	printf("It's the enemy's turn!");
	usleep(MILL_TO_MICRO(700));
	
	*state = EXIT;
}

//display boards for human
void displayBoards(Player *human, Player *computer)
{
	clear();
	printf("                 Enemy Board\n");
	printBoard(computer->board);
	printf("                 Your Board\n");
	printBoard(human->board);
}

void promptShot()
{
	printf("It's your turn! Where would you like to target?\n");
	printf("Please enter a letter followed by a number: ");
}

