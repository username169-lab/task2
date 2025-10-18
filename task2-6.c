#include <stdio.h>
#include <stdlib.h>
#define MAXLEN 100

typedef struct Node *link;
typedef int elemtype;
typedef struct Node {
	elemtype elem;
	int count;
	link left;
	link right;
} node;
typedef link tree;

int check(tree t, elemtype x);
int add(tree *tp, elemtype x);
int delete(tree *tp, elemtype x);
void print(tree t);
void destroy(tree *tp);

int main(void) {
	tree t = NULL;
	elemtype x;
	char buf[MAXLEN + 1];

	printf("Enter an integer with a key +, - or ?:\n");
	while (scanf("%s", buf) == 1) {
		x = atoi(buf + 1);
		switch(buf[0]) {
		case '+':
			if (!add(&t, x)) {
				printf("ERROR: can't add element!\n");
			}
			break;
		case '-':
			if (!delete(&t, x)) {
				printf("ERROR: element not found or tree is empty!\n");
			}
			break;
		case '?':
			printf(check(t, x) ? "%d yes\n": "%d no\n", x);
			break;
		}
		printf("Tree state: ");
		print(t);
		printf("\n");
	}
	destroy(&t);

	return 0;
}

int check(tree t, elemtype x) {
	if (t == NULL) {
		return 0;
	} else if (x == t -> elem) {
		return t -> count;	
	} else if (x < t -> elem) {
		check(t -> left, x);
	} else {
		check(t -> right, x);
	}
}

int add(tree *tp, elemtype x) {
	if (*tp == NULL) {
		tree tmp = (link)calloc(1, sizeof(node));
		if (tmp == NULL) {
			return 0;
		}
		tmp -> elem = x;
		tmp -> count = 1;
		tmp -> left = NULL;
		tmp -> right = NULL;
		*tp = tmp;
		return 1;
	} else if (x == (*tp) -> elem) {
		((*tp) -> count)++;
		return 1;
	} else if (x < (*tp) -> elem) {
		add(&((*tp) -> left), x);
	} else {
		add(&((*tp) -> right), x);
	}
}

int delete(tree *tp, elemtype x) {
	if (*tp == NULL) {
		return 0;
	} else if (x == (*tp) -> elem) {
		tree tmp = *tp;
		tree l = (*tp) -> left;
		tree r = (*tp) -> right;
		if (l != NULL && r != NULL) {
			elemtype min_in_right = r -> elem;
			while (r -> left != NULL) {
				tmp = r;
				r = r -> left;
				min_in_right = r -> elem;
			}
			if (tmp != *tp) {
				tmp -> left = r -> right;
			} else {
				tmp -> right = r -> right;
			}
			free(r);
			(*tp) -> elem = min_in_right;
		} else if (l != NULL) {
			*tp = l;
			free(tmp);	
		} else {
			*tp = r;
			free(tmp);
		}
		return 1;
	} else if (x < (*tp) -> elem) {
		delete((&(*tp) -> left), x);
	} else {
		delete(&((*tp) -> right), x);
	}
}

void print(tree t) {
	if (t != NULL) {
		print(t -> left);
		printf("%d ", t -> elem);
		print(t -> right);
	}
}

void destroy(tree *tp) {
	if (*tp != NULL) {
		destroy((&(*tp) -> left));
		destroy((&(*tp) -> right));
		tree tmp = *tp;
		free(tmp);
		*tp = NULL;
	}
}
