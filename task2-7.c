#include <stdio.h>
#include <setjmp.h>

jmp_buf begin;
char curlex;
void getlex(void);
int expr(void);
int add(void);
int mult(void);
void error();

int main(void) {
	int result;

	setjmp(begin);
	printf("==>");
	getlex();
	result = expr();
	if(curlex != '\n')
		error();
	printf("\n%d\n", result);
	
	return 0;
}

void getlex() {
	while((curlex = getchar()) == ' ');
}

void error(void) {
	printf("\nERROR!\n");
	while(getchar() != '\n');
	longjmp(begin, 1);
}

int expr() {
	int e = add();
	while(curlex == '+' || curlex == '-') {
		if(curlex == '+') {
			getlex();
			e += add();
		} else {
			getlex();
			e -= add();
		}
	}
	return e;
}

int add() {
	int a = mult();
	int tmp;
	while(curlex == '*' || curlex == '/') {
		if(curlex == '*') {
			getlex();
			a *= mult();
		} else {
			getlex();
			tmp = mult();
			if(tmp)
				a = (int)(a/tmp);
			else
				error();
		}
	}
	return a;
}

int mult() {
	int m;
	int tmp, p = 1;
	switch(curlex) {
	case '0': case '1': case '2': case '3': case '4': case '5':
	case '6': case '7': case '8': case '9':
		m = curlex - '0';
		break;
	case '(': 
		getlex();
		m = expr();
		if(curlex == ')')
		      break;
	default:
		error();
	}
	getlex();
	if(curlex == '^') {
		getlex();
		tmp = mult();
		if(tmp >= 0) {
			for(int i = 0; i < tmp; p = p*m, i++);
			m = p;	
		} else
			error();
	}
	return m;
}
