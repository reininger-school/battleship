/*******************************************************************************************
* Programmer: Reid Reininger                                                               *
* Class: CptS 121, Spring  2017; Lab Section 11                                            *
* Programming Assignment: PA6                                                              *
* Date Started: March 26, 2017                                                             *
* Last Update: March 26, 2017                                                              *
*																						   *
*Description: This program is a game of battleship where the player plays against a	       *
*			  computer AI. The player has the option of manually placing ships or		   *
*			  allowing them to be placed randomly. There is a file named				   *
*			  "battleship.log" tp record the game stats.                                   *
*																						   *
*			                                                                               *
* Status: Commenting                                           		                       *
*******************************************************************************************/

//Guard Code
#ifndef PA6_HELP_H
#define PA6_HELP_H

//libraries
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

//debuggers: 1 for on, 0 for off
#define DEBUG 0 //prints grid with computer ship locations as well
#define QUICK_START 0 // skips opening cut scene
#define CHOOSE_SHOT 0 // allows selction of shot when AI tells the computer to shoot randomly

//player macros
#define PLAYER 1 //human
#define COMPUTER 2 //computer

//ship placement macros
#define ROWS 10
#define COLUMNS 10
#define DOWN 0
#define RIGHT 1

//board symbols
#define HIT 42 // "*"  
#define MISS 109 // "m"
#define WATER 32 // 45 = "-" 32 = " "

//directions
#define NORTH 0
#define SOUTH 2
#define EAST 1
#define WEST 3

//ships
#define NUMBER_OF_SHIPS 5
#define CARRIER 0
#define BATTLESHIP 1
#define CRUISER 2
#define SUBMARINE 3
#define DESTROYER 4

//structures

typedef struct {
	int total_hits;
	int total_misses;
	double hm_ratio;
} stats;

//////////////////////////////////////////////
//Function Prototypes
//////////////////////////////////////////////

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
void display_file(FILE *file);

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
void print_file(FILE *file);

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
void print_board(const char board[ROWS][COLUMNS]);

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
void initialize_game_board(char board[ROWS][COLUMNS]);

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
int determine_who_goes_first(void);

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
int prompt_if_manual_placement(void);

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
void place_ships_randomly(char board[ROWS][COLUMNS]);

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
void place_ships_manually(char board[ROWS][COLUMNS]);

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
void get_coordinate(int *row, int *column);

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
void start_game_sequence(void);

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
void player_shoot(int player, int *row_ptr, int *column_ptr, int *hm_ptr, int *hits, int *misses, char board_player[ROWS][COLUMNS],
				  char board_computer[ROWS][COLUMNS], char board_enemy[ROWS][COLUMNS]);

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
int check_if_shot_valid(int column, int row, int player, char board_player[ROWS][COLUMNS], char board_computer[ROWS][COLUMNS], char board_enemy[ROWS][COLUMNS]);

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
int check_if_hit(int column, int row, int player, char board_player[ROWS][COLUMNS], char board_computer[ROWS][COLUMNS], char board_enemy[ROWS][COLUMNS]);

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
void AI(int *direction, int *column, int *row, int *was_last_hms, int initial_hit[2], int *hit_streak);

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
void check_sunk_ship(char board[ROWS][COLUMNS], int ship_status[5]);

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
void record_shot(FILE *file, int player, int row, int column, int row_comp, int column_comp, int hm);

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
void print_stats(FILE *log, stats player, int winner, stats computer);

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
void print_game_boards(board_computer, board_enemy, board_player);

/************************************************************
* Function: computer_shoot()                                *
* Date Created: Apri1 3, 2017                               *
* Date Last Modified: Apri1 3, 2017                         *
* Description: computer takes fire against human player     *
* Input parameters: direction, column_comp, row_comp,       *
*					was_last_hms, initial_hit, hit_streak,  *
*					player, board player, computer, enemy;  *
*					hm, hits_computer, misses_computer      *
* Returns: nothing                                          *
* Preconditions:                                            *
* Postconditions:                                           *
*************************************************************/
void computer_shoot(int *direction_ptr, int *column_comp_ptr, int *row_comp_ptr, int *was_last_hms_ptr, int initial_hit[2], int *hit_streak_ptr,
	int player, int board_player[ROWS][COLUMNS], int board_computer[ROWS][COLUMNS], int board_enemy[ROWS][COLUMNS], int *hm_ptr, int *hits_computer_ptr, int *misses_computer_ptr);


//end guard code
#endif

