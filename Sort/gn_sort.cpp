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

int * gnome_sort(int a[], int n)
{
	int i=1, t;
	while(i<n)
	{
		if (a[i]<a[i-1])
		{
			t=a[i];
			a[i]=a[i-1];
			a[i-1]=t;
			if (i>1) i--;
		}
		else i++;
	}
	return a;
}

int main()
{
	int * p;
	int n;
	scanf("%d", &n);
	p=(int*)malloc(10*sizeof(int));
	readArr(p, n);
	gnome_sort(p, n);
	writeArr(p, n);
	return 0;
}
