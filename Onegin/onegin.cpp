#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include <stdlib.h>
#include "sortStr.cpp"
int cmpstringp(const void  *p1, const void* p2){
	return strcmp(*(char**)p1, *(char**)p2);
}

int main()
{
	int len[10000];
	int i=0, j, k, a, max;
	char s[10000][100];
	char * t;
	
	for (i=0; i<10000; i++)
	{
		for (j=0; j<100; j++)
		{
			s[i][j]=0;
		}
	}
		
	FILE * fp;
	FILE * my1_fp;
	fp=fopen("intout.txt", "r");
	my1_fp=fopen("output.txt", "w");
	
	for (i=0; i<10000; i++)
	{
		fscanf(fp, "%s", &s[i]);
	} 
	
	for(j=0; j<10000; j++)
	{	
		for (i=0; i<10000; i++)
		{
				sortStr(s[i], s[i+1]);
		}
	} 
	//qsort(&s[0], 10000, sizeof( char*) , cmpstringp);
	
	for (i=0; i<10000; i++)
	{
		fprintf(my1_fp, "%s", s[i]);
	
		fprintf(my1_fp, "\n");
	}
	fclose(my1_fp);
	fclose(fp);
	printf("finish");
	return 0;
}
