#include<stdio.h>
#include<malloc.h>

int * readArr(int a[], int n)
{
	int i;
	for (i=0; i<n; i++)
	{
		scanf("%d", &a[i]);
	}
	return a;
}

int * writeArr(int a[], int n)
{
	int i;
	for (i=0; i<n; i++)
	{
		printf("%d ", a[i]);
	}
	return a;
}

int * sort_sl(int arr1[], int lLeft, int arr2[], int lRight)
{
	//printf("\n#%d#   #%d# \n", lRight, lLeft);
	int * arr;
	int i=0; 
	int iLeft=0;
	int iRight=0;
	arr=(int*)malloc((lLeft+lRight)*sizeof(int));
	
	while (i<(lLeft+lRight))
	{
		if (((arr1[iLeft]<arr2[iRight]) || (iRight>=lRight)) && (iLeft<lLeft))
		{
			arr[i]=arr1[iLeft];
			iLeft++;
			//printf("*");
			//printf("arr[i]=%d i=%d a\n", arr[i], i);
		}
		
		else if (((arr1[iLeft]>=arr2[iRight]) || (iLeft>=lLeft)) && (iRight<lRight))
		{
			arr[i]=arr2[iRight];
			iRight++;
			//printf("^");
			//printf("arr[i]=%d i=%d b\n", arr[i], i);
		}
		i++;
	}
	//writeArr(arr2, lRight);
	printf("\n");
	return arr;
}

int * sort(int l, int arr[])
{
	int i, t;
	int lLeft;
	lLeft=l/2;
	int lRight=l-lLeft;
	int * arr1;
	int * arr2;
	arr1=(int *)malloc(lLeft*sizeof(int)); 
	arr2=(int *)malloc(lRight*sizeof(int));
	if ((lLeft>0) && (lRight>0))
	{
		if ((lLeft>1) && (lRight>1))
		{
			for (i=0; i<lLeft; i++)
			{
				arr1[i]=arr[i];
				//printf("%d ", arr1[i]);
			}
		
			for (i=lLeft; i<l; i++)
			{
				arr2[i-lLeft]=arr[i];
				//printf("%d ", arr2[i-lLeft]);
			}
			
			/*writeArr(arr1, lLeft);
			printf("\n");
			writeArr(arr2, lRight);*/
			arr1=sort(lLeft, arr1);
			arr2=sort(lRight, arr2);
			arr=sort_sl(arr1, lLeft, arr2, lRight);
			//writeArr(arr, lLeft+lRight);
		}
		if ((lLeft==1) && (lRight>1))
		{
			arr1[0]=arr[0];
			if (arr[1]>arr[2])
			{
				arr2[0]=arr[2];
				arr2[1]=arr[1];
			}
			else 
			{
				arr2[0]=arr[1];
				arr2[1]=arr[2];
			}
			arr=sort_sl(arr1, lLeft, arr2, lRight);
			//printf("%d %d\n", arr[1], arr[2]);
			//printf("\n");
			//writeArr(arr, lLeft+lRight);
		}
		if ((lLeft==1) && (lRight==1))
		{
			if (arr[0]>arr[1])
			{
				t=arr[0];
				arr[0]=arr[1];
				arr[1]=t;
			}
			//writeArr(arr, 2);
		}
	}

	free(arr1);
	free(arr2);
	return arr;
}

int main()
{
	int n;
	int * p;
	scanf("%d", &n);
	p=(int *)malloc(n*sizeof(int));
	readArr(p, n);
	p=sort(n, p);
	writeArr(p, n);
	free(p);
	return 0;
}
