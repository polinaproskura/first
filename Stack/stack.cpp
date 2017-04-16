#include <stdio.h>
#include<stdlib.h>

struct Stack 
{
	int l;
	int *p;
	p = ñalloc(100, sizeof(int));
};

struct Stack * Push(struct Stack * a)
{
	(*a).l++;
	scanf("%d", (*a).p[(*a).l-1]);
	return a;
}

int Pop(struct Stack *a)
{
	int i;
	i=(*a).p[(*a).l-1];
	(*a).l--;
	return i; 
}
