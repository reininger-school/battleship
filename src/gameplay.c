#include "../header/gameplay.h"

void humanTurn(State *state, Player *human, Player *computer)
{
	Coord target;
	ShotStatus status = 0;
	displayGameInfo(human, computer);
	promptTarget();
	target = getCoord();
	//check coord not previously targeted
	while (isTargeted(computer->board[target.row][target.column])){
		printf("You already targeted there. Please choose somewhere else.\n");
		target = getCoord();
	}
	status = fire(target, computer, human);
	printResult(status, target, computer);
	usleep(MILL_TO_MICRO(700));

	if (isAllSunk(computer))
		*state = ENDGAME;
	else
		*state = COMPUTER_TURN;
}

void computerTurn(State *state, Player *human, Player *computer)
{
	Coord target;
	static ShotStatus status = 0;
	displayGameInfo(human, computer);
	printf("It's the enemy's turn!");
	#ifndef QUICK_PLAY
	usleep(MILL_TO_MICRO(700));
	#endif
	target = computeComputerTarget(human, computer);
	status = fire(target, human, computer);
	printResult(status, target, human);

	if (isAllSunk(computer))
		*state = ENDGAME;
	else
		*state = HUMAN_TURN;
}

void displayGameInfo(Player *human, Player *computer)
{
	clear();
	printBoards(computer->board, human->board);
	putchar('\n');
	printf("Friendly Ship HP: ");
	printShips(human);
	putchar('\n');
}

void promptTarget()
{
	printf("It's your turn! Where would you like to target?\n");
	printf("Please enter a row letter followed by a column number: \n");
}

void printResult(ShotStatus status, Coord target, Player *player)
{
	char *str[] = {"hit", "miss", "hit"};
	printf("Firing");
	typewriter("....", 300);
	printf("It's a %s!\n", str[status]);
	if (status == SUNK){ //print ship if sunk
		printf("%s Has been sunk! Press enter to continue...",
				shipNameTab[player->board[target.row][target.column].entity]);
		enterToContinue();
	}
	else
		usleep(MILL_TO_MICRO(1000));
}

int isTargeted(Tile tile)
{
	return tile.targeted;
}

Bool isValid(Tile tile, Coord coord)
{
	return !tile.targeted && !isOutOfBounds(coord.row, coord.column);
}

int isSunk(Ship ship)
{
	return !ship.hp;
}

Bool existsUnsunk(Player *player)
{
	for (int i=0; i<N_SHIPS; i++){
		if (player->ships[i].hp < shipSizeTab[i] && player->ships[i].sunk)
			return TRUE;
	}
	return FALSE;
}

Bool isAllSunk(Player *player)
{
	for (int i=0; i<N_SHIPS; i++){
		if (!isSunk(player->ships[i]))
			return FALSE;
	}
	return TRUE;
}

ShotStatus fire(Coord target, Player *firee, Player *firer)
{
	Shot shot; //store shot data
	shot.entity = firee->board[target.row][target.column].entity;
	shot.target = target;
	firee->board[target.row][target.column].targeted = 1;
	if (shot.entity != WATER){//check hit
		firee->board[target.row][target.column].visible = HIT_CHAR;
		firee->ships[shot.entity].hp--;
		shot.hms = isSunk(firee->ships[shot.entity]) ? SUNK : HIT;
	}
	else{
		shot.hms = MISS;
		firee->board[target.row][target.column].visible = MISS_CHAR;
	}
	push(&firer->stack, shot);
	return shot.hms;
}

