/**
* @file ai.h
* @author Reid Reininger
* @contact reininger900@hotmail.com
* @brief Compute coord computer should fire at.
*
* Defines a state machine for how the computer should determine its shot.
* @warning AI is not complete, currently only fires randomly.
*/
#ifndef _AI_H__
#define _AI_H__

#include "types.h"
#include "util.h"
#include "gameplay.h"

typedef enum aiStates {
	AI_RAND, AI_RANDDIR, AI_SAMEDIR, AI_OPPDIR, AI_STACK
} AIStates;

typedef struct aiState {
	AIStates state; //current AI state
	Bool unsunk; //true if a ship is damaged and not sunk
	Direction dir; //dir AI should direct shots(not always relevant)
	ShotStatus hms; //result of previous shot
	Coord initialHit;
} AIState;

/**
* Compute where computer should target.
*
* @param human Human player
* @return Coord computer should target.
*/
Coord computeComputerTarget(Player *human, Player *computer);

/**
* Change state to next state.
*/
void transitionFunction(AIState *state, Player *human, Player *computer);

/**
* Transition function for AI_RAND.
*/
void AIRandTrans(AIState *state, Player *human, Player *computer);

/**
* Transition function for AI_RANDDIR.
*/
void AIRanddirTrans(AIState *state, Player *human, Player *computer);

/**
* Checks if adjacent squares to previous computer hit can be fired at.
*/
Bool existsAdjacentShot(Player *human, Coord coord);

/**
* Checks if shot in same direction can be fired at.
*/
Bool existsNextDirShot(Player *human, Coord coord, Direction dir);

/**
* Transition function for AI_SAMEDIR.
*/
void AISamedirTrans(AIState *state, Player *human, Player *computer);

/**
* Transition function for AI_OPDIR
*/
void AIOpdirTrans(AIState *state, Player *human, Player *computer);

/**
* Returns opposite direction.
*/
Direction switchDir(Direction dir);

/**
* Return random valid shot.
*
* @param state AI state.
* @param player Player to target.
*/
Coord randomShot(AIState *state, Player *human, Player *computer);

/**
* Returns random coord adjacent to previous shot. Checks OB and targeted.
*/
Coord randomDir(AIState *state, Player *human, Player *computer);

/**
* Returns next coord in direction AI is firing.
*/
Coord sameDir(AIState *state, Player *human, Player *computer);

/**
* Returns next coord in opposite didrection AI was firing.
*/
Coord oppDir(AIState *state, Player *human, Player *computer);

#endif
