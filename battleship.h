/*******************************************************************************************
* Programmer: Reid Reininger                                                               *
* Class: CptS 121, Spring  2017; Lab Section 11                                            *
* Programming Assignment: PA6                                                              *
* Date Started: March 28, 2019                                                             *
* Last Update: March 28, 2019                                                              *
*																						   *
*Description: This program is a game of battleship where the player plays against a	       *
*			  computer AI. The player has the option of manually placing ships or		   *
*			  allowing them to be placed randomly. There is a file named				   *
*			  "battleship.log" tp record the game stats.                                   *
*			                                                                               *
* Status: Commenting                                           		                       *
*******************************************************************************************/
#ifndef _HEADER_H__
#define _HEADER_H__

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//debuggers: 1 for on, 0 for off
#define DEBUG 0 //prints grid with computer ship locations as well
#define QUICK_START 0 // skips opening cut scene
#define CHOOSE_SHOT 0 // allows selction of shot when AI tells the computer to shoot randomly

//ship placement macros
#define ROWS 10
#define COLUMNS 10
#define DOWN 0
#define RIGHT 1
#define N_SHIPS 5

//board symbols
#define HIT_CHAR 42 // "*"  
#define MISS_CHAR 109 // "m"
#define WATER_CHAR 32 // 45 = "-" 32 = " "

//directions
typedef enum direction {
	NORTH, EAST, SOUTH, WEST
} Direction;

//ships
typedef enum boardEntity {
	CARRIER, BATTLESHIP, CRUISER, SUBMARINE, DESTROYER, WATER
} BoardEntity;

//game states
typedef enum state {
	SPLASH, RULES, SETUP, HUMAN, COMPUTER, ENDGAME, EXIT
} State;

//ship struct
typedef struct ship {
	char symbol;
	int size;
	int hp;
	int sunk;
} Ship;

typedef struct tile {
	BoardEntity entity;//entity occupying board tile
	char visible;//char to be printed for tile
} Tile;

typedef struct stats{
	int total_hits;
	int total_misses;
	double hm_ratio;
} Stats;

typedef struct player{
	Tile board[ROWS][COLUMNS];
	Ship ships[N_SHIPS];
	Stats stats;
} Player;

//////////////////////////////////////////////
//Function Prototypes
//////////////////////////////////////////////

int runApp();
void displaySplash(State *state, Player *human, Player *computer);
void displayRules(State *state, Player *human, Player *computer);
void setupGame(State *state, Player *human, Player *computer);
void initializePlayer(Player *player);
void initializeBoard(Tile board[ROWS][COLUMNS]);
void initializeShips(Ship ships[]);
void initializeStats(Stats *stats);
void placeHumanShips();
void placeComputerShips();
void placeShipsRandomly(Tile board[ROWS][COLUMNS]);
int randomPlayer();
void displayPregameCutscene();

#endif
