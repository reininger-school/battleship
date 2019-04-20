#include "../header/util.h"

char buf[BUF_SIZE]; 

void clear()
{
	system("clear");
}

void fprint(char *path)
{
	FILE *file = fopen(path, "r");
	if (file) //check file opened
		while(putchar(fgetc(file)) != EOF);
	else
		printf("Error: could not open %s\n", path);
	fclose(file);
}

void typewriter(char *str, int milli)
{
	while (*str){
		putchar(*str++);
		fflush(stdout);
		#ifndef QUICK_PLAY
		usleep(MILL_TO_MICRO(milli));
		#endif
	}
}

void printCoord(Coord coord)
{
	printf("%c%d", coord.row+'A', coord.column);
}

void printBoard(Tile board[ROWS][COLUMNS])
{
	char c = 0;
	int i = 0;
	FILE *format = fopen("rsrc/art/Board.txt", "r");
	if (format){//check file open
		while ( (c = fgetc(format)) != EOF){
			if (c == '%'){
				putchar(board[i/COLUMNS][i%ROWS].visible);
				i++;
			}		
			else
				putchar(c);
		}
	}
	else
		printf("Error: could not open rsrc/art/Board.txt\n");
	fclose(format);
}

void printBoards(Tile board0[ROWS][COLUMNS], Tile board1[ROWS][COLUMNS])
{
	char c = 0;
	int i[2] = {0, 0};
	int file = 0; //track which board is being printed
	FILE *format[2] = {fopen("rsrc/art/Board.txt", "r"),
					   fopen("rsrc/art/Board.txt", "r")};

	if (format[0] && format[1]){//check files open
		printf("                  Enemy Board                                    Friendly Board\n");
		while(c != EOF){
			while ( (c = fgetc(format[file])) != '\n' && c != EOF){
				if (c == '%'){
					putchar(!file ? board0[i[file]/COLUMNS][i[file]%ROWS].visible
							: board1[i[file]/COLUMNS][i[file]%ROWS].visible);
					i[file]++;
				}
				else if (c == '\r');
				else
					putchar(c);
			}
			printf("%s", file ? "\n" : "\t");
			file = !file;
		}
		putchar('\n');
	}
	else
		printf("Error: could not open rsrc/art/Board.txt\n");
	fclose(format[0]);
	fclose(format[1]);			
}

void printShips(Player *player)
{
	for (int i=0; i<N_SHIPS; i++){
		printf("%s ", shipNameTab[i]);
		for (int j=0; j<player->ships[i].hp; j++)
			putchar('O');
		for (int j=player->ships[i].hp; j<shipSizeTab[i]; j++)
			putchar('X');
		putchar(' ');
	}
	putchar('\n');
}

void enterToContinue()
{
	while (getchar() != '\n');
}

char *getUserInput(char *buf, int size)
{
	fgets(buf, size, stdin);
	if (buf[strlen(buf)-1] != '\n')//clear buf
		while(getchar() != '\n' && !feof(stdin));
	else
		buf[strlen(buf)-1] = 0;//remove newline
	return buf;
}

int getInt()
{
	char *endptr;
	int result = (int)strtol(getUserInput(buf, BUF_SIZE), &endptr, 10);
	while (*buf == 0 || *endptr != 0){
		printf("Error: invalid input, please enter an integer value: ");
		result = (int)strtol(getUserInput(buf, BUF_SIZE), &endptr, 10);
	}
	return result;
}

int getIntRange(int low, int high)
{
	int result;
	while ( (result = getInt()) < low || result >= high)
		printf("Error: please enter an integer between %d and %d: ",
				low, high-1);
	return result;
}

int getYN()
{
	getUserInput(buf, BUF_SIZE);
	while(!match(buf, "^[yYnN]$")){
		printf("Invalid input, please enter y or n: ");
		getUserInput(buf, BUF_SIZE);
	}
	return match(buf, "[yY]");
}

int getRD()
{
	getUserInput(buf, BUF_SIZE);
	while (!match(buf, "^[rRdD]$")){
		printf("Invalid input, please enter r or d: ");
		getUserInput(buf, BUF_SIZE);
	}
	return match(buf, "[rR]");
}

Coord getCoord()
{
	Coord result;
	char c;
	getUserInput(buf, BUF_SIZE);
	while (!match(buf, "^[a-jA-J]\\s*[0-9]$")){
		printf("Error: invalid input, please enter a letter (row) followed by a number(column):\n");
		getUserInput(buf, BUF_SIZE);
	}
	sscanf(buf, " %c%d", &c, &result.column);
	result.row = tolower(c) - 'a';
	return result;
}

int match(const char *str, const char *pattern)
{
	regex_t re;
	int status = 0;
	if (regcomp(&re, pattern, REG_NOSUB)) //error
		return -1;
	status = !regexec(&re, str, 0, 0, 0);
	regfree(&re);
	return status;
}

int randRange(const int low, const int high)
{
	return low + rand() % (high - low);
}


int randomPlayer()
{
	return randRange(0, 2);
}

