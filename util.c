#include "util.h"

//prints file to stdout
void fprint(char *path)
{
	FILE *file = fopen(path, "r");
	if (file) //check file opened
		while(putchar(fgetc(file)) != EOF);
	else
		printf("Error: could not open %s\n", path);
	fclose(file);
}

//clears screen
void clear()
{
	system("clear");
}

//returns integer in [low, high)
int randRange(const int low, const int high)
{
	return low + rand() % (high - low);
}


//NOT COMPLETE
void printBoard(Tile board[ROWS][COLUMNS])
{
	char c;
	FILE *format = fopen("art/Board.txt", "r");
	if (format){//check file open
		c = fgetc(format);
		while (!feof(format) && c != '%');
	}
}
