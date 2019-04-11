#ifndef _UTIL_H__
#define _UTIL_H__

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <regex.h>
#include "battleship.h"

#define BUF_SIZE 32
#define MILL_TO_MICRO(X) (X * 1000)

extern char buf[BUF_SIZE]; //buffer for user input functions
extern const char *shipNameTab[];
extern const char shipSymbolTab[];
extern const int shipSizeTab[];

void fprint(char* path);
void clear();
int randRange(int low, int high);
void printBoard(Tile board[ROWS][COLUMNS]);
char *getUserInput(char* buf, int size);
int getYN();
int isYN(char *buf);
int getInt();
int getIntRange(int low, int high);
void typewriter(char* str, int milli);
int match(const char *str, const char *pattern);
int isYN2(char *buf);
void printCoord(Coord coord);
int getRD();
Coord getCoord();
void enterToContinue();
void printBoards(Tile board1[ROWS][COLUMNS], Tile board2[ROWS][COLUMNS]);
void printShips(Player *player);

#endif
