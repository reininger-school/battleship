#include "../header/setup.h"

void setupGame(State *state, Player *human, Player *computer)
{
	srand(time(NULL));
	initializePlayer(human);
	initializePlayer(computer);
	placeComputerShips(computer);
	*state = PLACE_SHIPS;
}

void initializePlayer(Player *player)
{
	initializeBoard(player->board);
	initializeShips(player->ships);
	initializeStats(&player->stats);
}

void initializeBoard(Tile board[ROWS][COLUMNS])
{
	for (int i=0; i<ROWS; i++){
		for (int j=0; j<COLUMNS; j++){
			board[i][j].entity = WATER;
			board[i][j].visible = WATER_CHAR;
			board[i][j].targeted = 0;
		}
	}
}

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
