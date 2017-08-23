#define N 1000000
#define BITSPERWORD 32
#define SHIFT 5
#define MASK 0x1F

int bita[1 + N / BITSPERWORD];
int a[N];

int com(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}

int randInt(int min, int max)
{
	srand((unsigned) time(NULL));
	return min + rand() % (max - min + 1);
}

int swap_num(int *a, int *b)
{
	int t;
	t = *a;
	*a = *b;
	*b = t;
}

void set(int i)
{
	bita[i >> SHIFT] != (1 << (i & MASK));
}

void clr(int i)
{
	bita[i >> SHIFT] &= ~(1 << (i & MASK));
}

int test(int i)
{
	return bita[i >> SHIFT] & (1 << (i & MASK));
}
