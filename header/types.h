/**
* @file types.h
* @author Reid Reininger
* @contact reininger900@hotmail.com
* @brief Constants and user defined types
*
* @note Debugging macros defined here
*/
#ifndef _TYPES_H__
#define _TYPES_H__

//#include "shotStack.h"

//debuggers
//#define QUICK_PLAY //remove all animations and cutscenes
//#define SHOW_ENEMY //show enemy ship positions
//#define PRINT_AI_STATE //print state of AI every computer turn
//#define CHOOSE_AI_RAND //choose wher AI shoots in AI_RAND state

//ship placement macros
#define ROWS 10
#define COLUMNS 10
#define DOWN 0
#define RIGHT 1
#define N_SHIPS 5
#define MAX_SHIP_NAME 16
#define VISIBLE 1
#define INVISIBLE 0

//board symbols
#define HIT_CHAR 42 // "*"  
#define MISS_CHAR 109 // "m"
#define WATER_CHAR '~' // 45 = "-" 32 = " "
#define STACK_SIZE 64


///table of names for ships, aligned with BoardEntity enum
extern const char *shipNameTab[];
///table of ship board symbols
extern const char shipSymbolTab[];
///table of ship sizes
extern const int shipSizeTab[];

/**
* boolean 
*/
typedef enum bool {
	FALSE, TRUE
} Bool;

/**
* Coordinate with row and column for refering to board locations.
*/
typedef struct coord{
	int row;
	int column;
} Coord;

/**
* Cardinal directions
*
* Used for AI
*/
typedef enum direction {
	NORTH, EAST, SOUTH, WEST
} Direction;

/**
* Result of shot
*/
typedef enum shotStatus {
	HIT, MISS, SUNK
} ShotStatus;

/**
* Entities occupying board tiles
*/
typedef enum boardEntity {
	CARRIER, BATTLESHIP, CRUISER, SUBMARINE, DESTROYER, WATER
} BoardEntity;

/**
* Game states
*/
typedef enum state {
	SPLASH, RULES, SETUP, PLACE_SHIPS, CUTSCENE, HUMAN_TURN, COMPUTER_TURN, ENDGAME,
	EXIT
} State;

/**
* Data for individual ships.
*
* Constants such as ship name, size, and board symbol can be looked up in
* global tables in types.h using the ships entity field.
*/
typedef struct ship {
	BoardEntity entity; //type of ship
	int hp; //health points
	Bool sunk;
} Ship;

/**
* Tiles to make up player boards.
*
* The player struct contains boards which are 2-D arrays of this tile class.
* The visible field is the character that is printed when the board is printed
* out, allowing the entity to be in/visible.
*/
typedef struct tile {
	BoardEntity entity;//entity occupying board tile
	char visible;//char to be printed for tile
	Bool targeted;
} Tile;

/**
* Stats fields for players hits and misses throughout the game.
*/
typedef struct stats{
	int total_hits;
	int total_misses;
	double hm_ratio;
} Stats;

/**
* Shot data.
*/
typedef struct shot{
	Coord target;
	ShotStatus hms;
	BoardEntity entity;
} Shot;

/**
* Stack data structure for shots.
*
* Array implementation.
*/
typedef struct shotStack{
	Shot base[STACK_SIZE];
	Shot *maxTop;
	Shot *top;
} ShotStack;

/**
* Data needed for each player.
*/
typedef struct player{
	Tile board[ROWS][COLUMNS];
	Ship ships[N_SHIPS];
	Stats stats;
	ShotStack stack;
} Player;

#endif
