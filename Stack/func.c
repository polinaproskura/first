#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//int lab[5];

/*

TODO:
	-	Названия переменных должны быть выразительными!!!!
	-	См. п. 1!!!!!
	-	Общее форматирование кода:
		* 	"2 - 3" а не "2-3"
		* 	struct Stack* p или struct Stack *p 	
	-	Проверки
		*	calloc и malloc могут возвратить NULL, то есть ВСЕГДА нужно проверять
			возвращенный указатель
		*	fopen() также может возвратить NULL --- проверять
	- 	Выбери свой стиль (обоснованный) и следуй ему
	-	КОНСТАНТЫ !!! Никаких непонятных чисел в коде
	-	Никаких уровней вложности более трех
	
*/


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

int jmp(int buff_j1)
{
	int i;
	FILE * lab_f;
	lab_f=fopen("lab.txt", "r");
	int lab[5];
	for (i = 0; i < 5; i++)
	{
		fscanf(lab_f ,"%d", &lab[i]);
	}
	printf("\nlab=%d\n", lab[buff_j1]);
	return lab[buff_j1];	
}

/*int je(int buff_j, int a)
{
	if (a==1) return jmp(buff_j);	
}*/

int Pop(struct Stack *a)
{
	int i;
	i = (*a).p[(*a).l - 1];
	(*a).l--;
	return i; 
}

struct Stack * add(struct Stack * a)
{
	int i;
	i=Pop(a) + Pop(a);
	Push(a, i);
	return a;
}

struct Stack * lea(struct Stack * a, int t)
{
	int k = 1;
	int i;
	for (i = 0; i < t; i++)
	{
		k = 2 * k;
	}
	i=Pop(a) + k * Pop(a);
	printf("k = %d, t = %d, i = %d", k, t, i);
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

int mov (int * x, int k)
{
	(*x)=k;
	return (*x);
}

struct Stack * push_x (struct Stack * a, int * x)
{
	(*a).l++;
	(*a).p[(*a).l-1]=(*x);
	return a;
}

int * pop_x (struct Stack * a, int * x)
{
	(*x)=(*a).p[(*a).l-1];
	(*a).l--;
	return x;
}

int * inc (int * x)
{
	(*x)++;
	return x;
}

int * dec (int * x)
{
	(*x)--;
	return x;
}

int jne(int buff_j1, int * x)
{
	printf("buff=%d x=%d|\n", buff_j1, (*x));
	if ((*x) > 0) return jmp(buff_j1);
	return buff_j1;
}

void assembl(FILE * wtd, FILE * arr, char c[][10])
{
	int lab[5];
	FILE * lab_f;
	lab_f=fopen("lab.txt", "w");
	char b[7];
	int k, r;
	int j = 0;
	int i = 100;
	int d;
	int a;
	char z[2];
	FILE* length;
	length = fopen("length.txt", "w");
	
	for (i = 0; i < 5; i++)
	{
		lab[i]=0;
	}
	
	do
	{
		j++;
		fscanf(wtd,"%s",b);
		if (b[0] == ':')
		{
			lab[(int)b[1]-48]=j;
		}
	} while (strcmp(b, c[0]) != 0);
	
	fclose(wtd);
	wtd=fopen("whattodo.txt", "r");
	
	j=0;
	
	do 
	{
		j++;
		fscanf(wtd,"%s",b);
		
		if (b[0] == ':') 
		{
			j--;
			//fscanf(wtd, "%s", b);
		}
		
		else 
		{
			//printf("$");
			if (strcmp(b, c[1]) == 0)  
			{
				i=1;
				fscanf(wtd, "%d", &k);
			}
			
			if (strcmp(b, c[2]) == 0)  i=2;
			
			if (strcmp(b, c[0]) == 0)  i=0;
			
			if (strcmp(b, c[3]) == 0)  i=3;
			
			if (strcmp(b, c[4]) == 0)  i=4;
			
			if (strcmp(b, c[5]) == 0)  i=5;
			
			if (strcmp(b, c[6]) == 0)  i=6;
			
			if (strcmp(b, c[7]) == 0)  
			{
				i=7;
				fscanf(wtd, "%d", &k);
			}
			
			if (strcmp(b, c[8])  == 0)  i=8;
			
			if (strcmp(b, c[9])  == 0)  i=9;
			
			if (strcmp(b, c[10]) == 0)  i=10;
			
			if (strcmp(b, c[11]) == 0)  i=11;
			
			if (strcmp(b, c[12]) == 0)  
			{
				fscanf(wtd, "%d", &k);
				i=12;
			}
			
			if (strcmp(b, c[13]) == 0)  
			{
				fscanf(wtd, "%d", &k);
				i=13;
			}
			
			if (strcmp(b, c[14]) == 0)  
			{
				i=14;
			}
			
			if (strcmp(b, c[15]) == 0)
			{
				fscanf(wtd, "%d", &k);
				i=15;
			}
			
			if ((i == 1) || (i == 7) || (i == 12) || (i == 13) || (i == 15))
			{
				fprintf(arr, "%d %d ", i, k);
				j++;
			}
			
			else if	(i < 100)
					{
						fprintf(arr, "%d ", i);
					}
			//printf("%d", i);
		}
	} while (strcmp(b, c[0]) != 0);
	fprintf(length, "%d", j);
	for (i = 0; i < 5; i++)
	{
		fprintf(lab_f ,"%d ", lab[i]);
	}
	return;
}
