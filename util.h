#ifndef _UTIL_H__
#define _UTIL_H__

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include "battleship.h"

#define BUF_SIZE 32
#define MILL_TO_MICRO(X) (X * 1000)

extern char buf[BUF_SIZE]; //buffer for user input functions

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

#endif
