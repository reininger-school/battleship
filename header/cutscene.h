/**
* @file cutscene.h
* @author Reid Reininger
* @contact reininger900@hotmail.com
* @brief Functions for cutscene functionality.
*
* Functions for SPLASH, RULES, and CUTSCENE states.
*/
#ifndef _CUTSCENE_H__
#define _CUTSCENE_H__

#include "types.h"
#include "util.h"

/**
* Displays title splash screen.
* 
* Behavior for SPLASH state. Should only be called by runApp().
* @Functionality disabled when QUICK_PLAY is defined.
* @param state Game state.
*/
void displaySplash(State *state, Player *human, Player *computer);

/**
* Displays rules screen.
* 
* Behavior for RULES state. Should only be called by runApp().
* @Functionality disabled when QUICK_PLAY is defined.
* @param state Game state.
*/
void displayRules(State *state, Player *human, Player *computer);

/**
* Animated cutscene before gameplay starts..
* 
* Behavior for CUTSCENE state. Should only be called by runApp().
* @Functionality disabled when QUICK_PLAY is defined.
* @param state Game state.
*/
void displayPregameCutscene();

#endif
