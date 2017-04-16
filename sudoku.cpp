#include<stdio.h>

int main()
{
	int a[9][9];
	int s[81][9]; //s[9*i+j];
	for (i=0; i<81; i++)
	{
		for (j=0; j<9; j++)
		{
			s[i][j]=j+1;
		}
	}
	for (i=0; i<9; i++)
	{
		for (j=0; j<9; j++)
		{
			scanf("%d", a[i][j]);
		}
	}
	
	for (k=1; k<10; k++)
	{
		
		for (i=0; i<9; i++)
		{
			for (j=0; j<9; j++)
			{
				s[i*9+j][k]=k;	
				if ((a[i][j]==k) || (a[i][j]==k)) s[i*9+j][k]=0;
			}
		}
		for (l=0; l<9; l=l+3)
		{
			for (m=0; m<9; m=m+3)
			{
				for (j=l; j<l+3; j++)
				{
					for (i=m; i<m+3; i++)
					{
						if (a[i][j]==k) s[i*9+j][k]=0;
					}
				}
			}
		}
	}
	
	return 0;
}
