#include <stdio.h>

double mySqrt(double x, double eps);

int main(void) {
	double eps, x;

	printf("Enter eps = ");
	scanf("%lf", &eps);
	printf("Enter x:\n");
	while(scanf("%lf", &x) == 1)
		if(x <= 0)
			printf("Can't compute!\n");
       		else
			printf("sqrt(x) = %.10g\n", mySqrt(x, eps));

	return 0;
}

double mySqrt(double x, double eps) {
	double prev, curr = 1, diff;

	do {	
		prev = curr;
		curr = 0.5*(prev + x/prev);
		diff = prev - curr;
	} while (diff >= eps || diff <= -eps);

	return curr;
}
