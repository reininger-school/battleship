/**
* @file battleship.h
* @author Reid Reininger
* @contact reininger900@hotmail.com
* @brief Defines function running battleship application.
*/
#ifndef _HEADER_H__
#define _HEADER_H__

#include "types.h"
#include "cutscene.h"
#include "setup.h"
#include "placeShips.h"
#include "gameplay.h"

//initial game state
#define START_STATE SPLASH

/**
* Runs battleship application.
* 
* Application is designed as a state machine. The main game loop calls the
* function to execute the behavior of the current state. The state variable is
* changed by the state functions to transition to the next state.
*/
int runApp();

#endif
