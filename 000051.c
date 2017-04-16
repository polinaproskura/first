#include<stdio.h>
#include<math.h>

int q_equat()
{
	double a, b, c, x1, x2, x;
	printf("enter your coefficients\n");
	scanf("%lg %lg %lg", &a, &b, &c);
	if (a == 0)
	{
		if (b == 0)
		{
			if (c == 0)
			{
				printf("infinitely many solutions\n");
			}
			else
			{
				printf("no solutions\n");
			}
		}
		else
		{
			x = -c/b;
			if (x == -0) 
			{
				x = 0;
			}
			printf("x=%lg\n", x);
		}
	}
	else
	{
		if ((b*b-4*a*c) >= 0)
		{
			x2 = (-b-sqrt(b*b-4*a*c))/(2*a);
			x1 = (-b+sqrt(b*b-4*a*c))/(2*a);
			if (x1 == -0)
			{
				x1 = 0;
			}
			if (x2 == -0)
			{
				x2 = 0;
			}
			if (x1 == x2)
			{
				printf("x=%lg\n", x1);
			}
			else
			{
				if (x1 > x2)
				{
					printf ("x1=%lg x2=%lg\n", x2, x1);
				}
				else
				{
					printf("x1=%lg x2%lg\n", x1, x2);
				}
			}
		}
		else
		{
			printf("no real roots");
		}
	}
	return 0;
}

int main()
{
	q_equat();
	return 0;
}
