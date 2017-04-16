#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Stack 
{
	int l;
	int * p;
};

struct Stack * Push(struct Stack * a, int k)
{
	(*a).l++;
	(*a).p[(*a).l-1]=k;
	return a;
}

int Pop(struct Stack *a)
{
	int i;
	i=(*a).p[(*a).l-1];
	(*a).l--;
	return i; 
}

struct Stack * add(struct Stack * a)
{
	int i;
	i=Pop(a)+Pop(a);
	Push(a, i);
	return a;
}

struct Stack * sub(struct Stack * a)
{
	int i;
	i=Pop(a)-Pop(a);
	Push(a, i);
	return a;
}

struct Stack * mul(struct Stack * a)
{
	int i;
	i=Pop(a)*Pop(a);
	Push(a, i);
	return a;
}

struct Stack * Div(struct Stack * a)
{
	int i;
	i=Pop(a)/Pop(a);
	Push(a, i);
	return a;
}

int main()
{
	FILE * fp;
	FILE * fp_1;
	FILE * pf;
	pf=fopen("out.txt", "w");
	fp_1=fopen("commands.txt", "r");
	fp=fopen("whattodo.txt", "r");
	struct Stack a; 
	a.p = (int *) calloc(100, sizeof(int));
	a.l = 0;
	char b[4];
	char c[7][5];
	int i;
	for (i=0; i<7; i++)
	{
		fscanf(fp_1, "%s", c[i]);
		printf("%d-", i);
		puts(c[i]);
		//printf("*");
	}
 	i=8;
 	int k;
	do 
	{
		fscanf(fp, "%s",b);
		//fprintf(fp, "%d", b);
		//printf("%d-push\n", strcmp(b, c[1]));
		//printf("%d-pop\n", strcmp(b, c[2]));
		//printf("%d-end\n", strcmp(b, c[0]));
		
		if (strcmp(b, c[1]) == 0)  i=1;
		if (strcmp(b, c[2]) == 0)  i=2;
		if (strcmp(b, c[0]) == 0)  i=0;
		if (strcmp(b, c[3]) == 0)  i=3;
		if (strcmp(b, c[4]) == 0)  i=4;
		if (strcmp(b, c[5]) == 0)  i=5;
		if (strcmp(b, c[6]) == 0)  i=6;
		//printf("i=%d\n", i);
		
		/*switch (i)
		{
			case 1: 
				fscanf(fp, "%d", &k);
				//fprintf(fp, "%d", k);
				Push(&a, k);
				i=8;
				break;
			case 2: 
				fprintf(pf,"%d\n",Pop(&a));
				i=8;
				break;
			case 0: 
				i=0;
				break;
			case 3:
				add(&a);
				i=8;
				break;
			case 4:
				sub(&a);
				i=8;
				break;
			case 5:
				mul(&a);
				i=8;
				break;
			case 6:
				Div(&a);
				i=8;
				break;
			default : break; 
		}*/
		
	} while (i!=0);
	fclose(fp_1);
	fclose(fp);
	return 0;
}

