/**
* @file shotStack.h
* @author Reid Reininger
* @contact reininger900@hotmail.com
* @brief Stack data structute for shots.
*
* Full ascending stack.
*/
#ifndef _SHOT_STACK_H__
#define _SHOT_STACK_H__

#include <stdio.h>
#include "util.h"
#include "types.h"


/**
* Initialize stack.
*/
void initStack(ShotStack *stack);

/**
* Return true if stack is empty.
*/
Bool isEmpty(ShotStack *stack);

/**
* Return True if stack is full.
*/
Bool isFull(ShotStack *stack);

/**
* Push
*
* @return True on successful push.
*/
Bool push(ShotStack *stack, Shot shot);

/**
* Peek
*/
Shot peek(ShotStack *stack);

/**
* Pop
*
* @return copy of popped item.
*/
Shot pop(ShotStack *stack);

/**
* Return top pointer.
*/
Shot *getTop(ShotStack *stack);

/**
* Return base pointer.
*/
Shot *getBase(ShotStack *stack);

/**
* Return maxTop pointer.
*/
Shot *getMaxTop(ShotStack *stack);

/**
* Return shot with most recent hit.
*/
Shot *getLastHit(ShotStack *stack);

/**
* Print contents of stack to file.
*/
void fprintStack(FILE *file, ShotStack *stack);

#endif
