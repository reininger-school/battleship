/**
* @file util.h
* @author Reid Reininger
* @contact reininger900@hotmail.com
* @brief Utility functions not belonging to any particular state or game
* process.
*
* Contains functions for IO, randomness.
*/
#ifndef _UTIL_H__
#define _UTIL_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <regex.h>
#include "types.h"

#define BUF_SIZE 32
#define MILL_TO_MICRO(X) (X * 1000)

extern char buf[BUF_SIZE]; ///<buffer for user input functions

//////////////////////////////
//print functions
//////////////////////////////

/**
* Clears screen.
*/
void clear();

/**
* Prints file at path to stdout.
*/
void fprint(char* path);

/**
* Prints string one character at a time spaced by given milliseconds.
*
* Print text with typewriter effect.
* @param str String to print.
* @param milli time between printing characters in milliseconds.
*/
void typewriter(char* str, int milli);

/**
* Prints coordinate.
*/
void printCoord(Coord coord);

/**
* Prints board.
*/
void printBoard(Tile board[ROWS][COLUMNS]);

/**
* Prints two boards side by side.
*/
void printBoards(Tile board1[ROWS][COLUMNS], Tile board2[ROWS][COLUMNS]);

/**
* Prints HP of players ships.
*/
void printShips(Player *player);

//////////////////////////////
//input functions
//////////////////////////////
/**
* Prompts user to press enter, then waits for enter press.
*
* @note Clears buffer of all keypresses before enter.
*/
void enterToContinue();

/**
* Safely read a line from stdin to buf without newline
*
* All characters that do not fit in the buffer are discarded.
* @param buf Buffer string is read into.
* @param size Size of buf.
* @return buf.
*/
char *getUserInput(char* buf, int size);

/**
* Return integer from the user.
*/
int getInt();

/**
* Return int in [low, high) from user.
*/
int getIntRange(int low, int high);

/**
* Get yes or no from user.
*
* @return 1 for yes 0 for no.
*/
int getYN();

/**
* Get right or down from user.
*
* @return 1 for right 0 for down.
*/
int getRD();

/**
* Returns (row, column) coord from user.
*/
Coord getCoord();

//////////////////////////////
//misc
//////////////////////////////

/**
* Check if string matches regex pattern.
*
* Regex expressed as string using formatting from regex.c lib.
* @return 1 if string matches regex.
*/
int match(const char *str, const char *pattern);

/**
* returns integer in [low, high)
*/
int randRange(int low, int high);

/**
* returns 0 or 1.
*/
int randomPlayer();

#endif
