#include "./list.c"

int main()
{
	lnode *head, node;
	createList(head);
	int i;
	for(i=1; i<6; i++) {
		node = createNode(i);
		insert(node, head);
	}

	node = head->next;
	while(node != NULL) {
		print("%d\n", node->element);
		node = node->next;
	}
	return 0;
}
