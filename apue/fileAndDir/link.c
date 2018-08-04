#include "../apueerr.h"

int main(int argc, char **argv)
{
	int ret;
	ret = link("./stat.c", "stat.link");
	printf("%d\n", ret);
}
