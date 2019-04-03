#ifndef _UTIL_H__
#define _UTIL_H__

#include <stdio.h>
#include <stdlib.h>
#include "battleship.h"

void fprint(char*);
void clear();
int randRange(int low, int high);
void printBoard(Tile board[ROWS][COLUMNS]);

#endif
