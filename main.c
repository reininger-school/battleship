#include "header.h"

int main(void)
{
	
	//file pointers
	FILE *title = NULL;
	FILE *rules = NULL;
	FILE *board = NULL;
	FILE *lose = NULL;
	FILE *log = fopen("battleship.log", "w");

	//boards
	char board_player[10][10], board_computer[10][10], board_enemy[10][10]; //baord_computer is the computer's board that the player can see; board_enemy holds computers ship placements

	//call srand one time only
	srand((unsigned int)time(NULL));

	//variables
	int player = 0;// records which players turn it is
	int player_ship_status[5] = { 1,1,1,1,1 }, computer_ship_status[5] = { 1,1,1,1,1 };//each element of these arrays represents the sunk status of a ship, 0 = sunk, 1 = still in play
	int player_ships_remaining = 5, computer_ships_remaining = 5;// how many ships each player has remaining
	char input = '\0'; //variable to hold player inputs

	//stat variables
	int hits_computer = 0, hits_player = 0, misses_computer = 0, misses_player = 0, hm; //record hits and misses
	int hits_computer_ptr = &hits_computer, hits_player_ptr = &hits_player, misses_computer_ptr = &misses_computer, misses_player_ptr = &misses_player, hm_ptr = &hm; //pointers to hit miss variables
	int winner; //records the game winner
	double player_hm_ratio, computer_hm_ratio; // hit miss ratios

	//stat structures
	stats player_stat = { 0, 0, 0 }, computer_stat = { 0, 0, 0 }; //structure for stats
	stats *player_stat_ptr = &player_stat, *computer_stat_ptr = &computer_stat;
	//AI variables
	int direction = -1, column = 0, column_comp = 0, row = 0, row_comp = 0, was_last_hms = 1, initial_hit[2] = { -1 , -1 }, hit_streak = 0;//records information from the last shot
	int *direction_ptr = &direction, *row_ptr = &row, *row_comp_ptr = &row_comp, *column_comp_ptr = &column_comp, *column_ptr = &column, *was_last_hms_ptr = &was_last_hms, *hit_streak_ptr = &hit_streak;//direction of last shot from initial hit


	while (1) //main loop
	{
		//////////////////////////////////////////////////
		//game setup
		//////////////////////////////////////////////////

		if (!(QUICK_START))
		{
			//display title page
			title = fopen("title.txt", "r");
			display_file(title);
			getch();

			//display welcome/rules page
			rules = fopen("rules.txt", "r");
			display_file(rules);
			getch();
		}

		//initialize game boards
		initialize_game_board(board_player);
		initialize_game_board(board_computer);
		initialize_game_board(board_enemy);

		//place computer's ships
		place_ships_randomly(board_computer);

		//player places ships manually or randomly
		if (prompt_if_manual_placement())
			place_ships_manually(board_player);
		else
			place_ships_randomly(board_player);
		
		//play starting game cut scene and determine which player is first
		if (!(QUICK_START))
			start_game_sequence();
		player = determine_who_goes_first();
		
		///////////////////////////////////
		//Game loop
		///////////////////////////////////

		while (1)
		{
			//print game boards
			print_game_boards(board_computer, board_enemy, board_player);

			//if players turn, they fire
			if (player == PLAYER)
				player_shoot(player, row_ptr, column_ptr, hm_ptr, hits_player_ptr, misses_player_ptr, board_player, board_computer, board_enemy);

			//if computers turn, they fire
			else
			{
				printf("\nIt's the enemy's turn!\n\n");
				if(!(QUICK_START))
					_sleep(400);

				int count = 0;
				do
				{
					//AI function is the logic where the computer decides where to shoot
					AI(direction_ptr, column_comp_ptr, row_comp_ptr, was_last_hms_ptr, initial_hit, hit_streak_ptr);
					count++;

					//fail-safe: if AI cannot find a valid shot based on logic, shoot anywhere randomly
					if (count > 20)
						was_last_hms = 1;

					//while the shot is not valid, continue to search for a valid shot
				} while (!(check_if_shot_valid(column_comp, row_comp, player, board_player, board_computer, board_enemy)));

				//enemy is firing animation
				printf("Enemy is firing");
				if (!(QUICK_START))
				{
					for (int i = 0; i < 4; i++)
					{
						_sleep(300);
						printf(".");
					}
					_sleep(300);
				}

				//check if shot was hit or miss
				if (check_if_hit(column_comp, row_comp, player, board_player, board_computer, board_enemy))
				{
					board_player[row_comp][column_comp] = HIT;
					hm = 1;
					hits_computer++;

					//if first hit since a ship was sunk, set coordinates as the initial hit for AI logic
					if (was_last_hms == 1)
					{
						initial_hit[0] = row_comp;
						initial_hit[1] = column_comp;
					}
					was_last_hms = -1;
					printf("It's a hit!");
				}
				else
				{
					hm = 0;
					misses_computer++;
					board_player[row_comp][column_comp] = MISS;
					if (was_last_hms != 1)
						was_last_hms = 0;
					printf("It's a miss!");
				}
				
				
			}

			//record the turn in the battleship.log
			record_shot(log, player, row, column, row_comp, column_comp, hm);

			//end turn sequence
			if (player == PLAYER)
			{
				player = COMPUTER;
				check_sunk_ship(board_computer, computer_ship_status);
				if(DEBUG)
					printf("%d%d%d%d%d", computer_ship_status[0], computer_ship_status[1], computer_ship_status[2], computer_ship_status[3], computer_ship_status[4]);
				
				//if a ship was sunk this turn, print it to the screen
				for (int i = 0; i < NUMBER_OF_SHIPS; i++)
				{
					if (computer_ship_status[i] == -1)
					{
						char ship_name[15];
						computer_ship_status[i] = 0;
						switch (i)
						{
						case CARRIER:
							strcpy(ship_name, "carrier");
							break;

						case BATTLESHIP:
							strcpy(ship_name, "battleship");
							break;

						case CRUISER:
							strcpy(ship_name, "cruiser");
							break;

						case SUBMARINE:
							strcpy(ship_name, "submarine");
							break;

						case DESTROYER:
							strcpy(ship_name, "destroyer");
							break;

						
						}
						fprintf(log, "Computer's %s sunk\n", ship_name);
						printf(" Enemies %s has been sunk!\nPress any key to continue...", ship_name);
						getch();
					}

				}
			}
			else
			{
				player = PLAYER;
				check_sunk_ship(board_player, player_ship_status);
				for (int i = 0; i < NUMBER_OF_SHIPS; i++)
				{
					if (player_ship_status[i] == -1)
					{
						char ship_name[15];
						was_last_hms = 1;
						player_ship_status[i] = 0;
						switch (i)
						{
						case CARRIER:
							strcpy(ship_name, "carrier");
							break;

						case BATTLESHIP:
							strcpy(ship_name, "battleship");
							break;

						case CRUISER:
							strcpy(ship_name, "cruiser");
							break;

						case SUBMARINE:
							strcpy(ship_name, "submarine");
							break;

						case DESTROYER:
							strcpy(ship_name, "destroyer");
							break;
						
						
						}
						fprintf(log, "Player's %s sunk\n", ship_name);
						printf(" Your %s has been sunk!\nPress any key to continue...", ship_name);
						getch();
					}
					
				}
			}

			//reset ship status variables to zero so subsequent for loop can check how many are left
			player_ships_remaining = 0;
			computer_ships_remaining = 0;	
			
			for (int i = 0; i < 5; i++)
			{
				player_ships_remaining += player_ship_status[i];
				computer_ships_remaining += computer_ship_status[i];
			}

			
			//if any player has no ships, exit the main game loop
			if (player_ships_remaining == 0 || computer_ships_remaining == 0)
				break;

			//dramatic pause at end of each turn
			_sleep(1200);
			
			

		}

		//determine if won or loss and display appropriate scene
		if (player_ships_remaining == 0)
		{
			winner = COMPUTER;
			for (int i = 0; i < 5; i++)
			{
				if (i > 0)
					_sleep(1000);
				system("cls");
				_sleep(500);
				lose = fopen("lose.txt", "r");
				display_file(lose);
			}
		}

		else
		{
			winner = PLAYER;
			for (int i = 0; i < 5; i++)
			{
				if (i > 0)
					_sleep(1000);
				system("cls");
				_sleep(500);
				lose = fopen("win.txt", "r");
				display_file(lose);
			}
		}


		//calculate game stats
		player_stat.total_hits = hits_player;
		player_stat.total_misses = misses_player;
		player_stat.hm_ratio = (double)player_stat.total_hits / player_stat.total_misses;

		computer_stat.total_hits = hits_computer;
		computer_stat.total_misses = misses_computer;
		computer_stat.hm_ratio = (double)computer_stat.total_hits / computer_stat.total_misses;

		//print final game stats to the log
		print_stats(log, player_stat, winner, computer_stat);

		//prompt player if they would like to see the log
		printf("\n\n\nA record of this ferocious battle has been recorded in the battleship.log!");
		printf("\nWould you like to view the log? Y N");
		while (input != 'Y' && input != 'y' && input != 'N' && input != 'n')
			input = getch();
		if (input == 'Y' || input == 'y')
		{
			log = fopen("battleship.log", "r");
			display_file(log);
			printf("\n\nPress any key to continue...");
			getch();
		}

		return 0;
		

	}
	
	

}