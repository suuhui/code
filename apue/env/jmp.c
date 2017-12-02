#include "../apueerr.h"
#include <setjmp.h>

static void f1(int, int, int, int);
static void f2(void);

static jmp_buf jmpbuf;
static int globval;

int main(void)
{
	int autoval;
	register int regival;
	volatile int volaval;
	static int statval;

	globval = 1;
	autoval = 2;
	regival = 3;
	volaval = 4;
	statval = 5;
	if(setjmp(jmpbuf) != 0) {
		printf("after longjmp:\n");
		printf("glovalval = %d; autoval = %d; regival = %d; volaval = %d; statval = %d.\n", globval, autoval, regival, volaval, statval);
		//f1(autoval, regival, volaval, statval);
		exit(0);
	}

	globval = 95;
	autoval = 96;
	regival = 97;
	volaval = 98;
	statval = 99;

	f1(autoval, regival, volaval, statval);
	exit(0);
}

static void f1(int i, int j, int k, int l)
{
	printf("in f1():\n");
	printf("glovalval = %d; autoval = %d; regival = %d; volaval = %d; statval = %d.\n", globval, i, j, k, l);
	f2();
}

static void f2(void)
{
	longjmp(jmpbuf, 1);	
}

