#include "../header/ai.h"
#include "../header/shotStack.h"

Coord computeComputerTarget(Player *human, Player *computer)
{
	static AIState state = {AI_RAND, FALSE, NORTH, MISS};
	Coord (* const stateTable[])() = {
		randomShot, randomDir, sameDir, oppDir
	};
	Coord result;

	//update state based on previous shot's results
	state.unsunk = existsUnsunk(human);
	if (!isEmpty(&computer->stack))
		state.hms = getTop(&computer->stack)->hms;
	transitionFunction(&state, human, computer);

	#ifdef PRINT_AI_STATE
	char *AIStateTab[] = {"AI_RAND", "AI_RANDDIR", "AI_SAMEDIR", "AI_OPPDIR",
	"AI_STACK"};
	printf("\n*************\n%s\n*************\n", AIStateTab[state.state]);
	getchar();
	#endif

	result = stateTable[state.state](&state, human, computer);
	return result;
}

void transitionFunction(AIState *state, Player *human, Player *computer)
{
	void (* const AIStateTab[])() = {
		AIRandTrans, AIRanddirTrans, AISamedirTrans, AIOpdirTrans
	};
	AIStateTab[state->state](state, human, computer);
}

void AIRandTrans(AIState *state, Player *human, Player *computer)
{
	/*
	if (state->hms == HIT && existsAdjacentShot(human,
		getLastHit(&computer->stack)->target))
		state->state = AI_RANDDIR;
	*/
	state->state = AI_RAND;
}

void AIRanddirTrans(AIState *state, Player *human, Player *computer)
{
	if (!state->unsunk)
		state->state = AI_RAND;

	else if (state->hms == HIT){
		if (existsNextDirShot(human, getLastHit(&computer->stack)->target, state->dir))
			state->state = AI_SAMEDIR;
		else
			state->state = AI_STACK;
	}
}

void AISamedirTrans(AIState *state, Player *human, Player *computer)
{
	if (state->hms == SUNK && !state->unsunk)
		state->state = AI_RAND;
	else if (state->hms == SUNK)
		state->state = AI_STACK;
	/*
	else if (!existsNexDirShot(human, getLastHit(&computer->stack)->target,
			 state->dir)){
		if (!existsNexDirShot(human, state->initialHit, switchDir(state->dir)))
			state->state =  AI_STACK;
		else
			state->state = AI_OPPDIR;
	}
	*/
}

void AIOpdirTrans(AIState *state, Player *human, Player *computer)
{
	if (!state->unsunk && state->hms == SUNK)
		state->state = AI_RAND;
	else if (!existsNextDirShot(human, getLastHit(&computer->stack)->target, switchDir(state->dir))
			 || state->hms == MISS)
		state->state = AI_STACK;
}

Direction switchDir(Direction dir)
{
	switch(dir){
		case NORTH: return SOUTH; break;
		case SOUTH: return NORTH; break;
		case EAST: return WEST; break;
		case WEST: return EAST; break;
	}
	return NORTH;
}

Bool existsAdjacentShot(Player *human, Coord coord)
{
	Bool dirs[4] = {FALSE, FALSE, FALSE, FALSE};
	Coord target = coord;
	Coord adj = {target.column + 1, target.row};
	dirs[0] = isValid(human->board[adj.row][adj.column], adj);
	adj.row = target.row; adj.column = target.column-1;
	dirs[1] = isValid(human->board[adj.row][adj.column], adj);
	adj.row = target.row+1; adj.column = target.column;
	dirs[2] = isValid(human->board[adj.row][adj.column], adj);
	adj.row = target.row-1; adj.column = target.column;
	dirs[3] = isValid(human->board[adj.row][adj.column], adj);
	return dirs[0] || dirs[1] || dirs[2] || dirs[3];
}

Bool existsNextDirShot(Player *human, Coord coord, Direction dir)
{
	Coord target = coord;
	switch (dir){
		case NORTH: target.row++; break;
		case SOUTH: target.row--; break;
		case EAST: target.column++; break;
		case WEST: target.column--; break;
	}
	return isValid(human->board[target.row][target.column], target);
}

Coord randomShot(AIState *state, Player *human, Player *computer)
{
	Coord result;
	#ifndef CHOOSE_AI_RAND
	do {
		result = randCoord();
	} while (isTargeted(human->board[result.row][result.column]));
	#else
	result = getCoord();
	#endif
	state->initialHit = result;
	return result;
}

Coord randomDir(AIState *state, Player *human, Player *computer)
{
	Coord lastHit, result;
	result = lastHit = getLastHit(&computer->stack)->target;
	do{
		result = lastHit;
		state->dir = randRange(0, 4);
		switch(state->dir){
			case NORTH: result.row = lastHit.row + 1; break;
			case SOUTH: result.row = lastHit.row - 1; break;
			case EAST: result.column = lastHit.column + 1; break;
			case WEST: result.column = lastHit.column - 1; break;
		}
	}while (isTargeted(human->board[result.row][result.column]) ||
		isOutOfBounds(result.row, result.column));
	return result;
}

Coord sameDir(AIState *state, Player *human, Player *computer)
{ 
	Coord target = getLastHit(&computer->stack)->target;
	switch(state->dir){
		case NORTH: target.row++; break;
		case SOUTH: target.row--; break;
		case EAST: target.column++; break;
		case WEST: target.column--; break;
	}
	return target;
}

Coord oppDir(AIState *state, Player *human, Player *computer)
{
	Coord target = state->initialHit;
	switch(switchDir(state->dir)){
		case NORTH: target.row++; break;
		case SOUTH: target.row--; break;
		case EAST: target.column++; break;
		case WEST: target.column--; break;
	}
	return target;
}
