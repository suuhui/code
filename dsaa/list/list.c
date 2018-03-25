#include "../comm.h" 
#include "./list.h"

Lnode createNode(eType x)
{
	Lnode l;
	l = malloc(sizeof(lnode));
	if(l == NULL) {
		printf("malloc error");
		exit(1);
	}
	l->element = x;
	l->next = NULL;
	return l;
}

lnode createList(lnode l)
{
	l = createNode(0);
	return l;
}

/* Return true if l is empty */
int isEmpty(list l)
{
	return l->next == NULL;
}

/* Return true if p is the last position in list l */
int isLast(position p, list l)
{
	if(isEmpty(l))
		return FALSE;
	return p->next == NULL;
}

/* return the postion of x in l; NULL if not found */
position find(eType x, list l)
{
	if(isEmpty(l))
		return FALSE;
	
	position p;
	p = l->next;
	while(p != NULL && p->elemet == x)
		p = p->next;
	
	return p;
}

eType ldelete(eType x, list l)
{
	position p, tmpCell;
	p = findPrevious(x, l);

	if(!isLast(p, l)) {
		tmpCell = p->next;
		p->next = tmpCell->next;
		free(tmpCell);
	}
}

position findPrevious(eType x, list l)
{
	if(isEmpty(l))
		return FALSE;
	position p;
	p = l->next;
	while(p->next != NULL && p->next->element != x)
		p = p->next;
	
	return p;
}

void insert(position p, position head)
{
	position tmp = head->next;
	position q = head;
	while(tmp != NULL) {
		q = tmp;
		tmp = tmp->next;
	}
	q->next = p;
	p->next = NULL;
}

void deleteList(list l)
{
	position p, tmpNode;
	
	p = l->next;
	l->next = NULL;
	while(p != NULL) {
		tmpNode = p->next;
		free(p);
		p = tmpNode;
	}
}

postion header(list l)
{
	return l->next;
}

eType retrieve(postion p)
{
	return 1;	
}

