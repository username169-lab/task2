#include <stdio.h>
#include <time.h>

long iterFib(int num);
long recFib(int num);

int main(void) {
	int i;
	long n, start, finish;
	double t;

	printf("Enter the index i of a Fibonacci number:\n");
	while(scanf("%d", &i) == 1) {
		start = clock();
		n = iterFib(i);
		finish = clock();
		t = (double)(finish - start)/CLOCKS_PER_SEC;
		printf("%d-th Fibonacci number = %ld; "
				"Iterative time = %e\n", i, n, t);
		
		start = clock();
		n = recFib(i);
		finish = clock();
		t = (double)(finish - start)/CLOCKS_PER_SEC;
		printf("%d-th Fibonacci number = %ld; "
				"Recursive time = %e\n", i, n, t);
	}	

	return 0;
}

long iterFib(int num) {
	long prev = 0, curr = 1, next = 1;
	
	if(num) {
		for(int i = 0; i < num - 1; i++) {
			next = prev + curr;
			prev = curr;
			curr = next;
		}
		return next;
	} else
		return 0;
}

long recFib(int num) {	
	switch(num) {
	case 0:
		return 0;
	case 1:
		return 1;
	default:
		return recFib(num - 1) + recFib(num - 2);
	}
}
