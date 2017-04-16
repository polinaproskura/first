#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.c"



int main()
{
	FILE * arr;
	FILE * comm;
	FILE * wtd;
	arr = fopen("array.txt", "w");
	comm = fopen("commands.txt", "r");
	wtd = fopen("whattodo.txt", "r");
	char b[7];
	char c[16][10];
	int i;
	for (i = 0; i < 16; i++)
	{
		fscanf(comm, "%s", c[i]);
		printf("%d-", i);
		puts(c[i]);
	}
	assembl(wtd, arr, c);
	fclose(arr);
	fclose(comm);
	fclose(wtd);
	return 0;
}
