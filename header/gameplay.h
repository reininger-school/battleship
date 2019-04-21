/**
* @file gameplay.h
* @author Reid Reininger
* @contact reininger900@hotmail.com
* @brief Functions for gameplay.
*
* Functions for state HUMAN_TURN.
*/
#ifndef _GAMEPLAY_H__
#define _GAMEPLAY_H__

#include <stdio.h>
#include "types.h"
#include "util.h"
#include "ai.h"
#include "shotStack.h"
#include "placeShips.h"

/**
* Carry out behavior during human's turn.
*
* Behavior for HUMAN_TURN state.
* @param state Game state.
*/
void humanTurn(State *state, Player *human, Player *computer);

/**
* Carry out behavior during Computer's turn.
*
* Behavior for COMPUTER_TURN state.
* @param state Game state.
*/
void computerTurn(State *state, Player *human, Player *computer);

/**
* Prints human and computer boards, ship states.
*/
void displayGameInfo(Player *human, Player *computer);

/**
* Print prompt for coordinate to fire at.
*/
void promptTarget();

/**
* Print if shot was hit, miss, or sunk.
*
* @param status Status of shot.
* @param target Where shot was fired.
* @param player Targeted player.
*/
void printResult(ShotStatus status, Coord target, Player *player);

/**
* Checks if tile has been previously fired at.
*
* @param tile Tile to check.
* @return 1 if previously fired at, 0 otherwise.
*/
int isTargeted(Tile tile);

/**
* Checks if shot is valid.
*/
Bool isValid(Tile tile, Coord coord);

/**
* Checks if ship was sunk.
*
* @param ship Ship to check sunk status.
* @return 1 if ship is sunk, 0 otherwise.
*/
int isSunk(Ship ship);

/**
* Checks if player has damaged but not sunken ships.
*/
Bool existsUnsunk(Player *player);

/**
* Checks if player has any remaining ships.
*/
Bool isAllSunk(Player *player);

/**
* Fires a shot.
*
* Updates symbol of tile fired at to hit or miss. Updates ships hp if hit.
* @pre Must check if target has been previously fired at.
* @param target Tile to fire at.
* @param firee Player to fire at.
* @param firer Player firing.
* @return Result of shot, HIT, MISS, or SUNK.
*/
ShotStatus fire(Coord target, Player *firee, Player *firer);

#endif
