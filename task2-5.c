#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 100

typedef struct Node *link;
typedef char *elemtype;
typedef struct Node {
	elemtype elem;
	link next;
} node;
typedef link list;

void add_front(list *lp, elemtype x);
void delete_like_last(list *lp, elemtype x);
void print(list l);
void destroy(list *lp);

int main(void) {
	list l = NULL;
	char buf[MAXLEN + 1], *tmp_buf;
	int c, i = 0;

	printf("Type the sequence of words:\n");
	while ((c = getchar()) != EOF) {
		switch(c) {
		case '\n': case '\t': case ' ':
			if (i > 0) {
				buf[i] = '\0';
				tmp_buf = (char *)calloc(1, strlen(buf) + 1);
				strcpy(tmp_buf, buf);
				add_front(&l, tmp_buf);
				i = 0;
			}
			break;
		default:
			if (i > MAXLEN) {
				printf("ERROR: word too long!\n");
			} else {
				buf[i++] = c;
			}
		}	
	}
	if (i > 0) {
		buf[i] = '\0';
		tmp_buf = (char *)calloc(1, strlen(buf) + 1);
		strcpy(tmp_buf, buf);
		add_front(&l, tmp_buf);
		i = 0;
	}
	delete_like_last(&l, l -> elem);
	/*printf("TEST %s", l -> elem);*/
	printf("Transformed sequence:\n");
	print(l);
	printf("\n");
	destroy(&l);

	return 0;
}

void add_front(list *lp, elemtype x) {
	list tmp = (link)calloc(1, sizeof(node));
	tmp -> elem = x;
	tmp -> next = *lp;
	*lp = tmp;
}

void delete_like_last(list *lp, elemtype x) {
	if (*lp != NULL && (*lp) -> next != NULL) {
		list tmp = (*lp) -> next;
		delete_like_last(&(tmp -> next), x);
		if (!strcmp(tmp -> elem, x)) {	
			*lp = tmp -> next;
			free(tmp -> elem);
			free(tmp);
		}
	}
}

void print(list l) {
	if (l != NULL) {
		print(l -> next);
		printf("%s ", l -> elem);
	}
}

void destroy(list *lp) {
	if (*lp != NULL) {
		destroy(&((*lp) -> next));
		free(*lp);
	}
}
