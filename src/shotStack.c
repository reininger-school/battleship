#include "../header/shotStack.h"

void initStack(ShotStack *stack)
{
	stack->maxTop = &stack->base[STACK_SIZE-1];
	stack->top = NULL;
}

Bool isEmpty(ShotStack *stack)
{
	return (!stack->top);
}

Bool isFull(ShotStack *stack)
{
	return (stack->top == stack->maxTop);
}

Bool push(ShotStack *stack, Shot shot)
{
	if (isFull(stack))
		return FALSE;
	if (isEmpty(stack))
		stack->top = stack->base;
	else
		stack->top++;
	*stack->top = shot;
	return TRUE;
}

Shot peek(ShotStack *stack)
{
	return *stack->top;
}

Shot *getTop(ShotStack *stack)
{
	return stack->top;
}

Shot *getBase(ShotStack *stack)
{
	return stack->base;
}

Shot *getMaxTop(ShotStack *stack)
{
	return stack->maxTop;
}

Shot *getLastHit(ShotStack *stack)
{
	Shot *pCur = getTop(stack);
	while (pCur > getBase(stack) && pCur->hms == MISS){
		pCur--;
	}
	return pCur;
}

void fprintStack(FILE *file, ShotStack *stack)
{
	const char *strTab[] = {"hit", "missed", "sunk"};
	Shot *pCur = getBase(stack);
	while (pCur < getTop(stack)){
		fprintCoord(file, pCur->target);
		fprintf(file, " %s %s\n", strTab[pCur->hms],
				shipNameTab[pCur->entity]);
		pCur++;
	}
}
