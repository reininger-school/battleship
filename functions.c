#include "header.h"

/************************************************************
* Function: display_file()                                  *
* Date Created: March 26, 2017                              *
* Date Last Modified: March 26, 2017                        *
* Description: clears the screen and displays the text file *
* Input parameters: pointer to file to be displayed         *
* Returns: Nothing                                          *
* Preconditions: file must opened                           *
* Postconditions: file is closed                            *
*************************************************************/

void display_file(FILE *file)
{
	if (file)
	{
		system("cls");
		while (!feof(file))
		{
			char input;
			fscanf(file, "%c", &input);
			putc(input, stdout);
		}
		fclose(file);
	}
}

/************************************************************
* Function: print_file()                                    *
* Date Created: March 26, 2017                              *
* Date Last Modified: March 26, 2017                        *
* Description: prints the text file without clearing screen *
* Input parameters: pointer to file to be displayed         *
* Returns: Nothing                                          *
* Preconditions: file must opened                           *
* Postconditions: file is closed                            *
*************************************************************/

void print_file(FILE *file)
{
	if (file)
	{
		while (!feof(file))
		{
			char input;
			fscanf(file, "%c", &input);
			putc(input, stdout);
		}
		fclose(file);
	}
}

/************************************************************
* Function: print_board()                                   *
* Date Created: March 26, 2017                              *
* Date Last Modified: March 26, 2017                        *
* Description: prints a game board                          *
* Input parameters: the board to be printed                 *
* Returns: Nothing                                          *
* Preconditions: array must be 10x10                        *
* Postconditions:                                           *
*************************************************************/

void print_board(const char board[ROWS][COLUMNS])
{
	char input = '\0';
	int i = 0, j = 0;
	FILE *boardfile = fopen("Board.txt", "r");

	while (!feof(boardfile)) //loop continues until end of file is reached
	{
		fscanf(boardfile, "%c", &input);		
		if (input == '%') //if % place holder is reached, print the corresponding character from the board array
		{
			printf("%c", board[i][j]);
			j++;
			if (j == COLUMNS)
				i++, j = 0;
		}
		else
			printf("%c", input);
	}
	
	printf("\n");
	fclose(boardfile);
}

/************************************************************
* Function: initialize_game_board()                         *
* Date Created: March 26, 2017                              *
* Date Last Modified: March 26, 2017                        *
* Description: sets all of the values in gameboard to water *
* Input parameters: array of board to be initialized        *
* Returns: Nothing                                          *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/

void initialize_game_board(char board[ROWS][COLUMNS])
{
	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLUMNS; j++)
			board[i][j] = WATER;
}

/************************************************************
* Function: determine_who_goes_first()                      *
* Date Created: March 28, 2017                              *
* Date Last Modified: March 28, 2017                        *
* Description: randomly returns 1 or 2                      *
* Input parameters: none                                    *
* Returns: 1 or 2                                           *
* Preconditions: srand must be seeded                       *
* Postconditions:                                           *
*************************************************************/

int determine_who_goes_first(void)
{
	return rand() % 2 + 1;
}

/************************************************************
* Function: prompt_if_manual_placement()                    *
* Date Created: March 28, 2017                              *
* Date Last Modified: March 28, 2017                        *
* Description: clears screen and prompts the user if they   *
*              would like manual or random ship placement   *
* Input parameters: none                                    *
* Returns: 1 if manual, 0 if random                         *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/

int prompt_if_manual_placement(void)
{
	char input = '\0';
	int output;
	
	while (input != 'Y' && input != 'y')
	{
		FILE *command = fopen("command_center.txt", "r");
		system("cls");
		display_file(command);
		printf("Would you like to coordinate the positions of the ships in your\narmada or allow your captains to postition themselves?\n");
		printf("\n1. Position manually");
		printf("\n2. Position randomly");

		while (input != '1' && input != '2')
			input = getch();

		system("cls");
		command = fopen("command_center.txt", "r");
		display_file(command);
		if (input == '1')
		{
			output = 1;
			printf("You have chosen to position your ships yourself. Is this correct? Y N");
		}

		else if (input == '2')
		{
			output = 0;
			printf("You have chosen to allow your captains to position themselves. Is this correct? Y N");
		}

		while (input != 'Y' && input != 'y' && input != 'N' && input != 'n')
			input = getch();

	}

	return output;
}

/************************************************************
* Function: place_ships_randomly()                          *
* Date Created: March 28, 2017                              *
* Date Last Modified: March 28, 2017                        *
* Description: - place the ships in random places on the    *
*                board                                      *
*              - checks to make sure that ships are not     *
*			     placed on top of one another               *
*              - check to make sure ships aren't placed off *
*			     the board                                  *
* Input parameters: game board                              *
* Returns: nothing                                          *
* Preconditions: board must be initialized (all values      *
*                set to water)                              *
* Postconditions:                                           *
*************************************************************/

void place_ships_randomly(char board[ROWS][COLUMNS])
{
	
	int direction, length, check = 0;
	int row, column;
	char ship_code;

	//completes this loop once for every ship type
	for (int ship = 0; ship < NUMBER_OF_SHIPS; ship++)
	{	
		//set length and character place in board to match the ship type
		switch (ship)
		{
		case CARRIER:
			length = 5;
			ship_code = 'C';
			break;

		case BATTLESHIP:
			length = 4;
			ship_code = 'B';
			break;

		case CRUISER:
			length = 3;
			ship_code = 'R';
			break;

		case SUBMARINE:
			length = 3;
			ship_code = 'S';
			break;

		case DESTROYER:
			length = 2;
			ship_code = 'D';
			break;
		}
		
		//determine the orientaion of the ship
		direction = rand() % 2;
		
		do
		{
			check = 0;
			if (direction == RIGHT)
			{
				row = rand() % ROWS;
				column = rand() % (COLUMNS - length);

				for (int i = 0; i < length; i++)
				{
					if (board[row][column + i] != WATER)
						check = 1;
				}
			}

			else if (direction == DOWN)
			{
				column = rand() % COLUMNS;
				row = rand() % (ROWS - length);

				for (int i = 0; i < length; i++)
				{
					if (board[row + i][column] != WATER)
						check = 1;
				}

				
			}

		} while (check == 1);

		if (direction == RIGHT)
		{
			for (int i = 0; i < length; i++)
				board[row][column + i] = ship_code;
		}

		else
		{
			for (int i = 0; i < length; i++)
				board[row + i][column] = ship_code;
		}
	}
}

/************************************************************
* Function: place_ships_manually()                          *
* Date Created: March 28, 2017                              *
* Date Last Modified: March 28, 2017                        *
* Description: - allows the player to choose where ships    *
*                are placed                                 *
*              - checks if placement is on top of other     *
*			     ship or off the board                      *
* Input parameters: game board                              *
* Returns: nothing                                          *
* Preconditions: board must be initialized (all values      *
*                set to water)                              *
* Postconditions:                                           *
*************************************************************/

void place_ships_manually(char board[ROWS][COLUMNS])
{
	FILE *instructions = NULL;
	int direction, length, check = 0;
	int row, column, *row_ptr = &row, *column_ptr = &column;
	char ship_code, input = '\0';
	char ship_name[50];

	//completes this loop once for every ship type
	for (int ship = 0; ship < NUMBER_OF_SHIPS; ship++)
	{
		//set length and character place in board to match the ship type
		switch (ship)
		{
		case CARRIER:
			length = 5;
			ship_code = 'C';
			strcpy(ship_name, "carrier (5 tiles)");
			break;

		case BATTLESHIP:
			length = 4;
			ship_code = 'B';
			strcpy(ship_name, "battleship (4 tiles)");
			break;

		case CRUISER:
			length = 3;
			ship_code = 'R';
			strcpy(ship_name, "cruiser (3 tiles)");
			break;

		case SUBMARINE:
			length = 3;
			ship_code = 'S';
			strcpy(ship_name, "submarine (3 tiles)");
			break;

		case DESTROYER:
			length = 2;
			ship_code = 'D';
			strcpy(ship_name, "destroyer (2 tiles)");
			break;
		}

		while (input != 'Y' && input != 'y' || check == 1)
		{
			system("cls");
			instructions = fopen("manual_placement_instructions.txt", "r");
			display_file(instructions);
			print_board(board);
			printf("\nHow would you like to orient your %s? R (right) or D (down)", ship_name);

			while (input != 'D' && input != 'd' && input != 'R' && input != 'r')
				input = getch();
			if (input > 73)
				input -= 32;
			printf(" %c", input);
			if (input == 'D' || input == 'd')
				direction = DOWN;
			else
				direction = RIGHT;

			printf("\nWhere would you like the starting point to be?\n");
			get_coordinate(row_ptr, column_ptr);

			check = 0;
			if (direction == RIGHT)
			{
				if ((column + length) > 10)
					check = 1;
				for (int i = 0; i < length; i++)
				{
					if (board[row][column + i] != WATER)
						check = 1;
				}
			}

			else if (direction == DOWN)
			{
				if ((row + length) > 10)
					check = 1;
				for (int i = 0; i < length; i++)
				{
					if (board[row + i][column] != WATER)
						check = 1;
				}

			}

			if (check == 1)
			{
				input = '\0';
				printf("\nYou cannot place a ship on top of one already placed or off of the board.\nPress any key to continue...");
				getch();
			}
			else
			{
				printf("Are you sure this how you want to place your %s? Y N", ship_name);
				while (input != 'Y' && input != 'y' && input != 'N' && input != 'n')
					input = getch();
			}
		}
		if (direction == RIGHT)
		{
			for (int i = 0; i < length; i++)
				board[row][column + i] = ship_code;
		}

		else
		{
			for (int i = 0; i < length; i++)
				board[row + i][column] = ship_code;
		}
		input = '\0';

	}
}

/************************************************************
* Function: get_coordinate()                                *
* Date Created: March 28, 2017                              *
* Date Last Modified: March 28, 2017                        *
* Description: - Prompts user to enter a coordinate         *
*              - must be letter (upper or lower) followed   *
*			     by single digit                            *
*			   - any other input form causes a reprompt     *
*			   - converts input into number coordinates for *
*			     compatibility with board arrays            *
* Input parameters: none                                    *
* Returns: row and column of coordinate entered             *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/

void get_coordinate(int *row, int *column)
{
	int rowx, columnx, check;
	char input[100];

	do
	{
		check = 0;
		printf("Please enter a row letter follwed by a column number without a space: ");
		gets(input);
		if (input[0] < 65 || (input[0] > 74 && input[0] < 97) || input[0] > 106 || input[1] < 48 || input[1] > 58 || strlen(input) > 2)
		{
			printf("\nInvalid input.\n");
			check = 1;
		}
			
	} while (check == 1);

	if (input[0] > 64 && input[0] < 75)
		rowx = input[0] - 65;
	else
		rowx = input[0] - 97;
	columnx = input[1] - 48;

	*row = rowx;
	*column = columnx;
}

/************************************************************
* Function: start_game_sequence()                           *
* Date Created: March 28, 2017                              *
* Date Last Modified: March 28, 2017                        *
* Description: Cut scene that plays before game starts      *
* Input parameters: none                                    *
* Returns: nothing                                          *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/

void start_game_sequence(void)
{
	FILE *boom = fopen("boom.txt", "r");
	char str1[45] = "Your ships are maneuvering into position";
	char str2[60] = "The first shot has been fired!!! Engaging!!!";

	system("cls");
	for (int i = 0; i <= strlen(str1); i++)
	{
		_sleep(30);
		printf("%c", str1[i]);
	}
	for (int i = 0; i < 4; i++)
	{
		printf(".");
		_sleep(900);
	}
	printf("\n\n\n");
	print_file(boom);
	printf("\n\n\n\n");
	for (int i = 0; i <= strlen(str2); i++)
	{
		_sleep(35);
		printf("%c", str2[i]);
	}
	_sleep(800);
	system("cls");
}

/************************************************************
* Function: player_shoot()                                  *
* Date Created: March 28, 2017                              *
* Date Last Modified: March 28, 2017                        *
* Description: -entire player shoot sequence, calls         *
*               get_coordinate() and check_if_hit(), then   *
*			    prints result of the shot                   *
*              -adds result to hit miss statistics          *
* Input parameters: player, board_player, board_computer,   *
*                   board_enemy                             *
* Returns: row and column targeted, player hits and misses  *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/

void player_shoot(int player, int *row_ptr, int *column_ptr, int *hm_ptr, int *hits, int *misses, char board_player[ROWS][COLUMNS], char board_computer[ROWS][COLUMNS], char board_enemy[ROWS][COLUMNS])
{
	int row = 0, column = 0, hits1 = 0, misses1 = 0;
	int *row1_ptr = &row, *column1_ptr = &column;

	
	printf("\nIt's your turn! ");
	//chatter();
		
	//get target coordinates and ensure it has not already been targeted
	int count = 0;
	do
	{			
		if (count != 0)
			printf("\nYou have already targeted this area.\n");
		printf("Where would you like to target?\n");
		if (CHOOSE_SHOT == 0)
			get_coordinate(row1_ptr, column1_ptr);
		else
		{
			column = rand() % 10;
			row = rand() % 10;
		}
		count++;
	} while (!(check_if_shot_valid(column, row, player, board_player, board_computer, board_enemy)));

	//print firing animation
	printf("\nFiring");
	if (!(QUICK_START))
	{
		for (int i = 0; i < 4; i++)
		{
			_sleep(300);
			printf(".");
		}

		_sleep(300);
	}
	if (check_if_hit(column, row, player, board_player, board_computer, board_enemy))
	{
		board_enemy[row][column] = HIT;
		board_computer[row][column] = HIT;
		*hm_ptr = 1;
		hits1++;
		printf("It's a hit!");

	}

	else
	{
		board_enemy[row][column] = MISS;
		*hm_ptr = 0;
		misses1++;
		printf("It's a miss!");
	}

	*row_ptr = row;
	*column_ptr = column;
	*hits += hits1;
	*misses += misses1;
}

/************************************************************
* Function: check_if_shot_valid()                           *
* Date Created: March 28, 2017                              *
* Date Last Modified: March 28, 2017                        *
* Description: checks if shot is valid                      *
* Input parameters: row and column targeted, player, boards *
* Returns: 1 if valid, 0 if invalid                         *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/

int check_if_shot_valid(int column, int row, int player, char board_player[ROWS][COLUMNS], char board_computer[ROWS][COLUMNS], char board_enemy[ROWS][COLUMNS])
{
	int check = 0;
	if (player == PLAYER)
	{
		if (board_enemy[row][column] == WATER)
			check = 1;
	}
	else
	{
		if (board_player[row][column] != HIT && board_player[row][column] != MISS)
			check = 1;
		if (row > 9 || row < 0 || column > 9 || column < 0)
			check = 0;
	}
	return check;
}

/************************************************************
* Function: check_if_hit()                                  *
* Date Created: March 28, 2017                              *
* Date Last Modified: March 28, 2017                        *
* Description: checks if shot is hit or miss                *
* Input parameters: row and column targeted, player, boards *
* Returns: 1 if hit, 0 if miss                              *
* Preconditions: must check if shot is valid first          *
* Postconditions:                                           *
*************************************************************/

int check_if_hit(int column, int row, int player, char board_player[ROWS][COLUMNS], char board_computer[ROWS][COLUMNS], char board_enemy[ROWS][COLUMNS])
{
	int check = 0;
	if (player == PLAYER)
	{
		if (board_computer[row][column] != WATER)
			check = 1;
	}
	else
		if (board_player[row][column] != WATER)
				check = 1;
	return check;
}

/************************************************************
* Function: AI()                                            *
* Date Created: March 28, 2017                              *
* Date Last Modified: March 28, 2017                        *
* Description: decides best shot for computer based on      *
*              previous hits and misses                     *
* Input parameters: direction from initial hit, last shot   *
*                   coordinates, was last hit or miss,      *
*                   coordinates of initial hit, hit streak  *
* Returns: coordinates of next target                       *
* Preconditions:                                            *
* Postconditions: the shot may not valid, must be placed in *
*                 fail safe loop to reset was_last_hms to   *
*                 1 if no valid coordinate can be found     *
*************************************************************/

void AI(int *direction, int *column, int *row, int *was_last_hms, int initial_hit[2], int *hit_streak)
{
	int direction1 = *direction, column1 = *column, row1 = *row, was_last_hms1 = *was_last_hms, hit_streak1 = *hit_streak;
	//if there hasn't been a hit since the last ship sunk, shoot anywhere on the board
	if (was_last_hms1 == 1)
	{
		
			hit_streak1 = 0;
			initial_hit[0] = -1;
			initial_hit[1] = -1;

		if (CHOOSE_SHOT == 0)
		{
			column1 = rand() % 10;
			row1 = rand() % 10;
		}
		else
		{
			printf("enter coordinates (both row and column as number) for computer shot: ");
			scanf("%d%d", &row1, &column1);
			printf("\n%d %d", row1, column1);
		}
	}

	else //last change: changed setting hit streak to one after rand direction
	{
		// if the last shot was a hit, fire one more tile in direction that hit was successful
		if (was_last_hms1 == -1)
			hit_streak1++;

		//1 if the shot was a miss but the one before was a hit and not sunk, start shooting in the opposite direction from the initial hit
		if ((was_last_hms1 == 0 && hit_streak1 > 1) || (was_last_hms1 == -1 && hit_streak1 > 1 && (row1 > 9 || row1 < 0 || column1 > 9 || column1 < 0)))
		{
			printf("\nopposite direction executed\n");
			if (direction1 == NORTH)
				direction1 = SOUTH;
			else if (direction1 == SOUTH)
				direction1 = NORTH;
			else if (direction1 == WEST)
				direction1 = EAST;
			else if (direction1 == EAST)
				direction1 = WEST;
			hit_streak1 = 1;
			
		}
		else if ((was_last_hms1 == -1 && hit_streak1 == 1) || was_last_hms1 == 0)
		{
			direction1 = rand() % 4;
		}

		if (direction1 == NORTH)
		{
			row1 = initial_hit[0] - hit_streak1;
			column1 = initial_hit[1];
		}

		else if (direction1 == SOUTH)
		{
			row1 = initial_hit[0] + hit_streak1;
			column1 = initial_hit[1];
		}

		else if (direction1 == WEST)
		{
			row1 = initial_hit[0];
			column1 = initial_hit[1] - hit_streak1;
		}

		else if (direction1 == EAST)
		{
			row1 = initial_hit[0];
			column1 = initial_hit[1] + hit_streak1;
		}

	}
	if (CHOOSE_SHOT)
		printf("(%d, %d)", row1, column1);

	*direction = direction1; *column = column1; *row = row1; *was_last_hms = was_last_hms1; *hit_streak = hit_streak1;


}

/************************************************************
* Function: check_sunk_ship()                               *
* Date Created: March 28, 2017                              *
* Date Last Modified: March 28, 2017                        *
* Description: checks if a ship is sunk                     *
* Input parameters: board, ship status array of player      *
* Returns: places 0 in the element of the ship status array *
           corresponding to any ships sunk                  *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/

void check_sunk_ship(char board[ROWS][COLUMNS], int ship_status[5])
{
	char ship_code;
	int ship_check[5] = {0, 0, 0, 0, 0};

	for (int ship = 0; ship < NUMBER_OF_SHIPS; ship++)
	{
		switch (ship)
		{
		case CARRIER:
			ship_code = 'C';
			break;

		case BATTLESHIP:
			ship_code = 'B';
			break;

		case CRUISER:
			ship_code = 'R';
			break;

		case SUBMARINE:
			ship_code = 'S';
			break;

		case DESTROYER:
			ship_code = 'D';
			break;
		}

		for (int i = 0; i < ROWS; i++)
			for (int j = 0; j < COLUMNS; j++)
				if (board[i][j] == ship_code)
					ship_check[ship]++;

		if (ship_check[ship] == 0 && ship_status[ship] == 1)
		{
			ship_status[ship] = -1;
		}
	}

}

/************************************************************
* Function: record_shot()                                   *
* Date Created: March 28, 2017                              *
* Date Last Modified: March 28, 2017                        *
* Description: records shot data in the battleship.log      *
* Input parameters: log file, player, row and column of     *
*                   shot for player and computer, hm        *
* Returns: nothing                                          *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/

void record_shot(FILE *file, int player, int row, int column, int row_comp, int column_comp, int hm)
{
	char c_row, c_column, s_hm[10], s_player[50];

	if (player == PLAYER)
	{
		c_row = row + 65;
		c_column = column + 48;
	}

	else
	{
		c_row = row_comp + 65;
		c_column = column_comp + 48;
	}

	if (player == PLAYER)
		strcpy(s_player, "Player shot:");
	else
		strcpy(s_player, "Computer shot:");
	if (hm == 1)
		strcpy(s_hm, "hit");
	else
		strcpy(s_hm, "miss");
	
	fprintf(file, "%s (%c, %c), %s\n", s_player, c_row, c_column, s_hm);
}

/************************************************************
* Function: print_stats()                                   *
* Date Created: March 28, 2017                              *
* Date Last Modified: March 28, 2017                        *
* Description: prints final game stats to the battleship.log*
* Input parameters: log file, stats player and computer     *
* Returns: nothing                                          *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/

void print_stats(FILE *log, stats player, int winner, stats computer)
{
	fprintf(log, "---------------------------------------------\n---------------------------------------------\n\n");
	if (winner == PLAYER)
		fprintf(log, "Player One Wins!\n");
	else
		fprintf(log, "Computer Wins!\n");
	fprintf(log, "\nPlayer Stats:\nHits: %d, Misses: %d, H/M ratio: %.2lf\n\n", player.total_hits, player.total_misses, player.hm_ratio);
	fprintf(log, "Computer Stats:\nHits: %d, Misses: %d, H/M ratio: %.2lf\n", computer.total_hits, computer.total_misses, computer.hm_ratio);
	fclose(log);
}

/************************************************************
* Function: print_game_boards()                             *
* Date Created: Apri1 3, 2017                               *
* Date Last Modified: Apri1 3, 2017                         *
* Description: prints all game boards                       *
* Input parameters: board_computer, board_enemy,            *
*                   board_player                            *
* Returns: nothing                                          *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/

void print_game_boards(board_computer, board_enemy, board_player)
{
	system("cls");
	printf("\n\n                 Enemy Grid\n");
	if (DEBUG)
		print_board(board_computer);
	print_board(board_enemy);
	printf("\n\n                 Friendly Grid\n");
	print_board(board_player);
}
