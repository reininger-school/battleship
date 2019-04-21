#include "../header/cutscene.h"

void displaySplash(State *state, Player *human, Player *computer)
{
	#ifndef QUICK_PLAY
	clear();
	fprint("rsrc/art/title.txt");
	enterToContinue();
	#endif
	*state = RULES;
}

void displayRules(State *state, Player *human, Player *computer)
{
	#ifndef QUICK_PLAY
	clear();
	fprint("rsrc/text/rules.txt");
	enterToContinue();
	#endif
	*state = SETUP;
}

void displayPregameCutscene(State *state, Player *human, Player *computer)
{
	#ifndef QUICK_PLAY
	char *str1 = "Your ships are maneuvering into position";
	char *str2 = "The first shot has been fired!!! Engaging!!!\n";

	clear();
	typewriter(str1, 30);
	typewriter("....", 900);
	printf("\n\n\n");
	fprint("rsrc/art/boom.txt");
	printf("\n\n\n\n");
	typewriter(str2, 35);
	usleep(MILL_TO_MICRO(800));
	printf("Press enter to continue...");
	enterToContinue();
	#endif

	//select random player to go first
	*state = randomPlayer() ? COMPUTER_TURN : HUMAN_TURN;
}

void displayWinCutscene(State *state, Player *human, Player *computer)
{

}
