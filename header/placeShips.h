/**
* @file placeShips.h
* @author Reid Reininger
* @contact reininger900@hotmail.com
* @brief Defines functions for placing ships on boards.
*
* Defines functionality for PLACE_SHIPS state and some of SETUP state.
*/
#ifndef _PLACE_SHIPS_H__
#define _PLACE_SHIPS_H__

#include <stdio.h>
#include "types.h"
#include "util.h"

/**
* Place computer's ships on board.
*
* Randomly places ships.
*/
void placeComputerShips(Player *computer);

/**
* Place human ships on board. 
*
* Defines behavior for PLACE_SHIPS state. Player can place ships manually or
* randomly. 
* @param state Game state. 
*/
void placeHumanShips(State *state, Player *human, Player *computer);

/**
* Print instructions for manually placing ships on the board. 
*
* @param board Board to place ships on. 
*/
void displayManualInstructions(Tile board[ROWS][COLUMNS]);

/**
* Print prompt to place ships manually or randomly.
*/
void promptPlacement();

/**
* Print prompt for orientation of ship placement.
*
* @param ship Ship to be placed.
*/
void promptOrientation(Ship ship);

/**
* Print prompt for starting point for ship placement.
*/
void promptStartingCoord();

/**
* Print prompt to confirm method of ship placement.
*/
void promptConfirmMethod(int method);

/**
* Print prompt to confirm position for ship placement.
*/
void promptConfirmPosition(Coord start, int dir);

/**
* Prompt and place ships on players board.
*
* @param player Player whose ships to place
* @param visible True to show ships when printed.
* @note Does not reset board to all water before placement.
*/
void placeShipsManually(Player *player, int visible);

/**
* Place ships randomly on board.
*
* @param player Player whose ships to place
* @param visible True to show ships when printed.
* @note Does not reset board to all water before placement.
*/
void placeShipsRandomly(Player *player, int visible);

/**
* Place ship randomly on board.
*
* @param ship Ship to be placed
* @param board Board to place ship on
* @param visible True to show ship when printed
* @return 1 if successfully placed.
*/
int placeShipRandomly(Ship ship, Tile board[ROWS][COLUMNS], int visible);

/**
* Place ship on board at given position.
*
* Ship is always placed, no checking for non-water entities. Check for out of
* bounds. The ship is placed starting at the given row and column then fills in
* the ship in the direction passed in.
* @param row Starting row.
* @param column Starting Column.
* @param dir Direction to fill in ship on board
* @param ship Ship to be placed.
* @param board Board to place ship on.
* @param visible True to show ships when printed
* @return 1 if ship successfully placed
*/
int placeShip(int row, int column, int dir, Ship ship,
			  Tile board[ROWS][COLUMNS], int visible);
/**
* returns 1 if ship can be place in passed in position.
*
* Checks if for out of bounds and non-water entities. Does not place ship.
*/
int checkShipFits(int row, int column, int dir, Ship ship, 
				  Tile board[ROWS][COLUMNS]);
/**
* returns 1 if coordinate is not out of bounds.
*/
int isOutOfBounds(int row, int column);

#endif

