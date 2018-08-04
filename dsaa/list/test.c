#include <stdio.h>

typedef struct tnode *Treeptr;
typedef struct tnode {
	char *word;
	int count;
	Treeptr *left;
} treenode;

int main()
{
	int i = sizeof(treenode);
	return 0;
}
