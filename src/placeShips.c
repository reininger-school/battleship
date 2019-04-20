#include "../header/placeShips.h"

void placeComputerShips(Player *computer)
{
	#ifndef SHOW_ENEMY
	placeShipsRandomly(computer, INVISIBLE);
	#else
	placeShipsRandomly(computer, VISIBLE);
	#endif
}

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

void displayManualInstructions(Tile board[ROWS][COLUMNS])
{
	clear();
	fprint("rsrc/art/manual_instructions.txt");
	printBoard(board);
}

void promptPlacement()
{
	fprint("rsrc/art/command_center.txt");
	printf("Would you like to coordinate the positions of the ships in your\n"\
		   "armada or allow your captains to position themselves?\n"\
		   "1. Place ships randomly\n"\
		   "2. Place ships manually\n");
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

void promptConfirmMethod(int method)
{
	if (method == 1)
		printf("You have elected to place your ships randomly. Is this"\
				" correct? (Y/n)\n");
	else
		printf("You have elected to place your ships manually. Is this"\
				"correct? (Y/n)\n");
}

void promptConfirmPosition(Coord start, int dir)
{
	printf("You have selected "); 
	printCoord(start);
	char *dirStr[] = {"down", "right"};
	printf(" %s to place your ship. Is this correct? (Y/n)\n",
			dirStr[dir]);
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

void placeShipsRandomly(Player *player, int visible)
{
	for (int i=0; i<N_SHIPS; i++){
		placeShipRandomly(player->ships[i], player->board, visible);
	}
}

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
	else{ //dir == RIGHT
		for (int i=0; i<shipSizeTab[ship.entity]; i++){
			board[row][column+i].entity = ship.entity;
			if (visible)
				board[row][column+i].visible = shipSymbolTab[ship.entity];
		}
	}
	return 1;
}

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
	else { //dir == RIGHT
		for (int i=0; i<shipSizeTab[ship.entity]; i++){
			if (isOutOfBounds(row, column+i) ||
				board[row][column+i].entity != WATER)
				return 0;
		}
	}
	return 1;
}

int isOutOfBounds(int row, int column)
{
	return (row < 0 || row >= ROWS ||
		column < 0 || column >= COLUMNS);
}

