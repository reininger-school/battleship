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
