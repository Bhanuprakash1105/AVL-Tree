#include <stdio.h>
#include <stdlib.h>

struct node {
	int d;
	struct node *r, *l, *p;
} *head;

#define COUNT 10

void display(struct node *trav, int space)
{
	if( trav == NULL ) {
		return;
	}
	
	space = space + COUNT;
	
	display( (*trav).r, space );
	
	printf("\n");
	for(int i = COUNT; i < space; i++) {
		printf(" ");
	}
	printf("%d\n", (*trav).d);
	
	display( (*trav).l, space );
}

int bf(struct node*);

void check(struct node*);

void LL(struct node*);

void RR(struct node*);

void LL_special(struct node*);

void RR_special(struct node*);

int height(struct node *trav) {
	if ( trav == NULL ) {
		return 0;
	}

	int	hls = height(trav->l) + 1;

	int hrs = height(trav->r) + 1;

	if ( hls >= hrs ) {
		return hls;
	} else {
		return hrs;
	}
}

void create(struct node *trav, int data) {
	struct node *new = (struct node*)malloc(sizeof(struct node));
	new->d = data;
	new->r = NULL;
	new->l = NULL;
	new->p = NULL;

	if ( trav == NULL ) {
		head = new;
		return;
	} else {
		struct node *prev;
		while (trav != NULL) {
			prev = trav;
			if ( data >= trav->d ) {
				trav = trav->r;
			} else {
				trav = trav->l;
			}
		}
		if ( data >= prev->d ) {
			prev->r = new;
		} else {
			prev->l = new;
		}
		new->p = prev;
	}

	check(new);
}

int main()
{
	int c = 0, d = 0;
Choice:	printf("\nPress: [1] Create  [2] Display  [3] Exit  >> ");
	scanf("%d", &c);

	switch (c) {
		case 1: printf("\nEnter a data: ");
				scanf("%d", &d);
				create(head, d);
				break;

		case 2: printf("\nThe AVL Tree: ");
				display(head, 5);
				printf("\n");
				d = height(head);
				printf("\nThe height of AVL tree is \"%d\"", d);
				printf("\n");
				break;

		case 3: printf("\nProgram Terminated\n\n");
				return 0;

		default: printf("\nInvalid input\n");
	}
	goto Choice;
}

int bf(struct node *trav) {
	if ( trav == NULL ) {
		return 0;
	}

	int hls = height(trav->l);

	int hrs = height(trav->r);

	return hls - hrs;
}

void check(struct node *trav) {
	if ( trav == NULL ) {
		return;
	}

	if ( bf(trav) < -1) {
		LL(trav);
	} else if ( bf(trav) > 1 ) {
		RR(trav);
	} else {
		check(trav->p);
	}
}

void RR(struct node *prob_node)
{
	struct node *left_child = prob_node->l;

	struct node *parent = prob_node->p;

	int flag = 0;
	if ( parent != NULL && parent->r == prob_node ) {
		flag = 10;
	} else if ( parent != NULL && parent->l == prob_node ) {
		flag = -10;
	}

	int hrs = height(left_child->r);
	int hls = height(left_child->l);

	if ( hrs > hls ) {
		LL_special(left_child);
		RR(prob_node);
		return;
	}

	struct node *right_of_LC = left_child->r;
	prob_node->l = right_of_LC;
	if ( right_of_LC != NULL ) {
		right_of_LC->p = prob_node;
	}

	left_child->r = prob_node;
	prob_node->p = left_child;

	left_child->p = parent;
	if ( flag == 10 ) {
		parent->r = left_child;
	} else if ( flag == -10 ) {
		parent->l = left_child;
	} else {
		head = left_child;
	}
}

void LL(struct node *prob_node)
{
	struct node *right_child = prob_node->r;
	
	struct node *parent = prob_node->p;

	int flag = 0;
	if ( parent != NULL && parent->r == prob_node ) {
		flag = 10;
	} else if ( parent != NULL && parent->l == prob_node ) {
		flag = -10;
	}

	int hrs = height(right_child->r);
	int hls = height(right_child->l);

	if ( hls > hrs ) {
		RR_special(right_child);
		LL(prob_node);
		return;
	}

	struct node *left_of_RC = right_child->l;
	prob_node->r = left_of_RC;
	if ( left_of_RC != NULL ) {
		left_of_RC->p = prob_node;
	}

	right_child->l = prob_node;
	prob_node->p = right_child;

	right_child->p = parent;
	if ( flag == 10 ) {
		parent->r = right_child;
	} else if ( flag == -10 ) {
		parent->l = right_child;
	} else {
		head = right_child;
	}
}

void LL_special(struct node *prob_node)
{
	struct node *right_child = prob_node->r;
	
	struct node *parent = prob_node->p;

	int flag = 0;
	if ( parent != NULL && parent->r == prob_node ) {
		flag = 10;
	} else if ( parent != NULL && parent->l == prob_node ) {
		flag = -10;
	}

	struct node *left_of_RC = right_child->l;
	prob_node->r = left_of_RC;
	if ( left_of_RC != NULL ) {
		left_of_RC->p = prob_node;
	}

	right_child->l = prob_node;
	prob_node->p = right_child;

	right_child->p = parent;
	if ( flag == 10 ) {
		parent->r = right_child;
	} else if ( flag == -10 ) {
		parent->l = right_child;
	} else {
		head = right_child;
	}	
}

void RR_special(struct node *prob_node)
{
	struct node *left_child = prob_node->l;

	struct node *parent = prob_node->p;

	int flag = 0;
	if ( parent != NULL && parent->r == prob_node ) {
		flag = 10;
	} else if ( parent != NULL && parent->l == prob_node ) {
		flag = -10;
	}

	struct node *right_of_LC = left_child->r;
	prob_node->l = right_of_LC;
	if ( right_of_LC != NULL ) {
		right_of_LC->p = prob_node;
	}

	left_child->r = prob_node;
	prob_node->p = left_child;

	left_child->p = parent;
	if ( flag == 10 ) {
		parent->r = left_child;
	} else if ( flag == -10 ) {
		parent->l = left_child;
	} else {
		head = left_child;
	}	
}