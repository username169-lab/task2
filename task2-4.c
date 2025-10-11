#include <stdio.h>
#define MAXLEN 100

double str2double(char str[]);

int main(void) {
	char str[MAXLEN];

	printf("Enter a real number:\n");
	while(scanf("%s", str) == 1)
		printf("%.10g\n", str2double(str));

	return 0;
}

double str2double(char str[]) {
	int sign = 1, p = 0;
	double x = 0, q = 1, pow = 1;
	char *ptr = str;

	while(*ptr != '\0' && *ptr != '.' && *ptr != 'e' && *ptr != 'E'\
			&& *ptr != 'f' && *ptr != 'F')
		x = x*10 + *ptr++ - '0';
	if(*ptr == '.') {
		ptr++;
		while(*ptr != '\0' && *ptr != 'e' && *ptr != 'E'\
			&& *ptr != 'f' && *ptr != 'F') {
			q = q*10;
			x = x + (*ptr++ - '0')/q;
		}
	}
       	if(*ptr == 'e' || *ptr == 'E') {
		if(*++ptr == '-')
			sign = 0;
		if(*ptr == '-' || *ptr == '+')
			ptr++;
		while(*ptr != '\0' && *ptr != 'f' && *ptr != 'F')
			p = p*10 + *ptr++ - '0';
		for(int i = 0; i < p; i++, pow = pow*10);
		x *= sign ? pow : 1/pow;
	}
	if(*ptr == 'f' || *ptr == 'F')
		x = (float)x;
	return x;
}
