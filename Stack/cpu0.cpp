#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.c"

int main()
{
	struct Stack a; 
	a.p = (int *) calloc(100, sizeof(int));
	a.l = 0;
	FILE * arr;
	FILE * res;
	int x;
	res=fopen("result.txt", "w");
	arr=fopen("array.txt", "r");
 	int i=100;
 	int k;
 	/*int j=0;
 	int buff[100];
 	buff[j]=100;
 	do
 	{
 		fscanf(arr, "%d", &buff[j]);
 		j++;
	} while (buff[j]!=0);
	int len=j;*/
 	do //for(j=0; j<len; j++)
 	{
 		fscanf(arr, "%d", &i);
 		//i=buff[j];
		switch (i)
		{
			case 1: 
				fscanf(arr, "%d", &k);
		//		j++;
		//		k=buff[j];
				Push(&a, k);
				i=100;
				break;
			case 2: 
				fprintf(res,"%d\n",Pop(&a));
				i=100;
				break;
			case 0: 
				i=0;
				break;
			case 3:
				add(&a);
				i=100;
				break;
			case 4:
				sub(&a);
				i=100;
				break;
			case 5:
				mul(&a);
				i=100;
				break;
			case 6:
				Div(&a);
				i=100;
				break;
			case 7:
				fscanf(arr,"%d", &k);
		//		j++;
		//		k=buff[j];
				mov(&x, k);
				i=100;
				break;
			case 8:
				push_x(&a, &x);
				i=100;
				break;
			case 9:
				pop_x(&a, &x);
				i=100;
				break;
			case 10:
				inc(&x);
				i=100;
				break;
			case 11:
				dec(&x);
				i=100;
				break;
			case 12:
		//		j++;
		//		j=jmp(buff[j]);
				i=100;
				break;
			case 13:
				i=100;
				break;
			case 14:
				i=100;
				break;
			default : break; 
		}
	} while (i!=0);
	fclose(arr);
	fclose(res);
	return 0;
}
