#ifndef _LIST_H

#define _LIST_H
typedef int eType;
typedef struct node *Lnode;
typedef struct node
{
	eType element;
	Lnode *next;
}lnode;
typedef struct lnode *PtrToLnode;
typedef PtrToLnode list;
typedef PtrToLnode position;

lnode createNode(eType x);
lnode createList(lnode l);
list makeEmpty(list l);
int isEmpty(list l);
int isLast(position p, list l);
position find(eType x, list l);
eType ldelete(eType x, list l);
position findPrevious(eType x, list l);
void insert(position p, list l);
void deleteList(list l);
position header(list l);
position first(list l);
position advance(position p);
eType retrieve(position p);

#endif /* _LIST_H_ */

