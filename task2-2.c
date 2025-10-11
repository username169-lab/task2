#include <stdio.h>

int main(void) {
	int n, pow;
	double x, res = 0, der = 0, step = 0, sum = 0, a;

	printf("Calculating values of polynomial, derivative and integral\n");
	printf("Enter the required sequence:\n");
	scanf("%d", &n);
	pow = n + 1;
	scanf("%lf", &x);
	while(scanf("%lf", &a) == 1) {
		res = res*x + a;
		
		der = der*x + step;
		step = step*x + a;

		sum = sum*x + a/pow;
		pow--;
	}
	sum *= x;
	sum = x > 0 ? sum : -sum;
	printf("Polynomial = %.10g\n", res);
	printf("Derivative = %.10g\n", der);
	printf("Integral = %.10g\n", sum);

	return 0;
}
