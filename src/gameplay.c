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
	status = fire(target, computer);
	printResult(status);
	if (status == SUNK){ //print ship if sunk
		printf("%s Has been sunk! Press enter to continue...",
				shipNameTab[computer->board[target.row][target.column].entity]);
		enterToContinue();
	}
	else
		usleep(MILL_TO_MICRO(1000));
	*state = HUMAN_TURN;
}

void computerTurn(State *state, Player *human, Player *computer)
{
	displayGameInfo(human, computer);
	printf("It's the enemy's turn!");
	#ifndef QUICK_PLAY
	usleep(MILL_TO_MICRO(700));
	#endif
	*state = EXIT;
}

void displayGameInfo(Player *human, Player *computer)
{
	clear();
	printBoards(computer->board, human->board);
	putchar('\n');
	printf("Friendly Ship HP: ");
	printShips(human);
	printf("Enemy Ship HP:    ");
	printShips(computer);
	putchar('\n');
}

void promptTarget()
{
	printf("It's your turn! Where would you like to target?\n");
	printf("Please enter a row letter followed by a column number: \n");
}

void printResult(ShotStatus status)
{
	char *str[] = {"hit", "miss", "hit"};
	printf("Firing");
	typewriter("....", 300);
	printf("It's a %s!\n", str[status]);
}

int isTargeted(Tile tile)
{
	return tile.targeted;
}

int isSunk(Ship ship)
{
	return !ship.hp;
}

ShotStatus fire(Coord target, Player *player)
{
	BoardEntity entity = player->board[target.row][target.column].entity;
	player->board[target.row][target.column].targeted = 1;
	if (entity != WATER){//check hit
		player->board[target.row][target.column].visible = HIT_CHAR;
		player->ships[entity].hp--;
		return isSunk(player->ships[entity]) ? SUNK : HIT;
	}
	player->board[target.row][target.column].visible = MISS_CHAR;
	return MISS;
}

