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
#define HIT 42 // "*"  
#define MISS 109 // "m"
#define WATER 32 // 45 = "-" 32 = " "

//directions
typedef enum direction {
	NORTH, EAST, SOUTH, WEST
} Direction;

//ships
typedef enum ship {
	CARRIER, BATTLESHIP, CRUISER, SUBMARINE, DESTROYER
} Ship;

//game states
typedef enum state {
	SPLASH, RULE, SETUP, HUMAN, COMPUTER, ENDGAME, EXIT
} State;

typedef struct stats{
	int total_hits;
	int total_misses;
	double hm_ratio;
} Stats;

//////////////////////////////////////////////
//Function Prototypes
//////////////////////////////////////////////

int runApp();
//states
//prints splash screen and waits for 
void splashScreen(State* state);

#endif
