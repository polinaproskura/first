#include<stdio.h>
#include<string.h>

void sortStr(char * s1, char * s2)
{
	int i, max;
	char t;
	if (strlen(s1)>strlen(s2)) max=strlen(s1)+1;
	else max=strlen(s2)+1;
	if (strcmp(s1, s2)>0)
	{
		for (i=0; i<max; i++)
		{
			t=s1[i];
			s1[i]=s2[i];
			s2[i]=t;
		}
	}
}

/*int main()
{
	char s1[50];
	char s2[50];
	gets(s1);
	gets(s2);
	sortStr(s1, s2);
	puts(s1);
	puts(s2);
	return 0;
}*/
