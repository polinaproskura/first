#include<stdio.h>
#include<ctype.h>

FILE * deleteSpace(FILE * file1)
{
	int i, k;
	FILE * file2;
	file2=fopen("intout.txt", "w");
	char s;
	for (i=0; i<1000000; i++)
	{
		fscanf(file1, "%c", &s);
		if (s!='\t') 
		{
			if (s==' ') 
			{
				s='_';
			}
			//s=tolower(s);
			fprintf(file2, "%c", s);
		}
	}
	return file2;
}

int main()
{
	FILE * file1;
	file1=fopen("input.txt", "r");
	deleteSpace(file1);
	return 0;
}
