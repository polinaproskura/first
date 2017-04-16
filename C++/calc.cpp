#include <stdio.h>
#include <malloc.h>

int main()
{
	char c;
	char * a;
	a=(char *) malloc(100* sizeof(char));
	int i=0;
	do
	{
		scanf ("%c", &c);
		if ((c >= '0') && (c <= '9')) 
		{
			a[i]=(int)c-48;
			i++;
		}
		if (c == '+')
		{
			a[i-2]=a[i-1]+a[i-2];
			i--;
		}
		if (c == '-')
		{
			a[i-2]=a[i-2]-a[i-1];
			i--;
		}
		if (c == '*')
		{
			a[i-2]=a[i-2]*a[i-1];
			i--;
		}
	}while (c != '=');
	printf("%d", a[i-1]);
	free(a);
	return 0;
}
