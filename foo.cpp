#include<stdio.h>

void foo(int * n)
{
	(*n)++;
	return;
}

int main()
{
	int a=5;
	foo(&a);
	printf("%d", a);
	return 0;
}
