#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.c"

int main()
{
	/*int o;
	FILE * lab_f;
	lab_f=fopen("lab.txt", "r");
	int lab[5];
	for (o = 0; o < 5; o++)
	{
		fscanf(lab_f ,"%d", &lab[o]);
		printf("%d ", lab[o]);
	}
	printf("\n");
	*/
	struct Stack a; 
	a.p = (int *) calloc(100, sizeof(int));
	a.l = 0;
	
	FILE * arr;
	FILE * res;
	
	int x;
	res = fopen("result.txt", "w");
	arr = fopen("array.txt", "r");
 	
	int i = 100;
 	int k = 1;
 	int j = 0;
 	int buff[100];
 	int N;
 	
	FILE * length;
 	length = fopen("length.txt", "r");
 	fscanf(length, "%d", &N);
 	
	for (j = 0; j < N; j++)
 	{
		fscanf(arr, "%d", &buff[j]);
		//printf("%d ", buff[j]);
	}	
	
	int len = j;
	int l = 0;
	//printf("%d", len);
	
	for(j = 0; j < len; j++)
 	{
 		l++;
 		if (l > 100) break;
 		i = buff[j];
		switch (i)
		{
			case 1: 
				j++;
				k = buff[j];
				Push(&a, k);
				//printf("\na=%d\n", a);
				i = 100;
				break;
			case 2: 
				//printf("\na=%d\n", a);
				fprintf(res,"%d\n",Pop(&a));
				i = 100;
				break;
			case 0: 
				i = 0;
				break;
			case 3:
				add(&a);
				i = 100;
				break;
			case 4:
				sub(&a);
				i = 100;
				break;
			case 5:
				mul(&a);
				i = 100;
				break;
			case 6:
				Div(&a);
				i = 100;
				break;
			case 7:
				j++;
				k = buff[j];
				mov(&x, k);
				i = 100;
				break;
			case 8:
				push_x(&a, &x);
				i = 100;
				break;
			case 9:
				pop_x(&a, &x);
				i = 100;
				break;
			case 10:
				inc(&x);
				i = 100;
				break;
			case 11:
				dec(&x);
				i = 100;
				break;
			case 12:
				jmp(buff[j+1]);
				i = 100;
				break;
			case 13:
				/*printf("\nx=%d\n", x);
				printf("\nbuff=%d\n", buff[j+1]);
				printf("\nj=%d\n", j);*/
				jne(buff[j+1], &x);
				i = 100;
				break;
			case 14:
				i = 100;
				break;
			case 15:
				j++;
				lea(&a, buff[j]);
				break;
			default : break; 
		}
	} 
	
	fclose(arr);
	fclose(res);
	return 0;
}
