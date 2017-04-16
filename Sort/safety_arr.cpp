#include<stdio.h>
#include<string.h>

int main()
{
	int i=0, j=0, k=0;
	char * str;
	str[0]='a';
	while (str[i]!='\0') {
		scanf("%c", &str[i]);
		if ((str[i]>='0') && (str[i]<='9')) {
			k++;
			i++;
			printf("*");
		}
		else if (str[i]==' ') {
			i++;
			printf("^");
		}
		else {
			i++;
			j++;
			printf("#");
		}
	}
	if ((j!=0) || (k!=10)) printf("ERROR\n");
	return 0;
}
