/**
* @file setup.h
* @author Reid Reininger
* @contact reininger900@hotmail.com
* @brief Functions for setting up the game.
*
* Functions for SETUP state.
*/

#ifndef _SETUP_H__
#define _SETUP_H__

#include <stdlib.h>
#include <time.h>
#include "types.h"
#include "placeShips.h"
#include "shotStack.h"

/**
* Setup for battleship game.
*
* Initializes computer and human players, places computer ships randomly, and
* seed rand().
* @param state Game state.
* @param human Human player.
* @param cmputer Computer player.
* @note should only be called by runApp().
*/
void setupGame(State *state, Player *human, Player *computer);

/**
* Initialize players board, ships, stats, and stack.
*/
void initializePlayer(Player *player);

/**
* Initialize all tiles in board array to water.
*
* Set each tile to water entity, print as a water tile, and never targeted.
*/
void initializeBoard(Tile board[ROWS][COLUMNS]);

/**
* Initialize a players array of ships.
*
* Start each ship with full health.
* @param ships player's array of ships to initialize.
* @pre ships must be of at least size 5.
*/
void initializeShips(Ship ships[]);

/**
* Initialze stats struct to all 0's.
*/
void initializeStats(Stats *stats);

#endif
