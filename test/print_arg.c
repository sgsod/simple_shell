#include <stdio.h>
#include <limits.h>
/**
  * main - entry point
  * Return: 0 (success)
  */
int main(int ac, char **av)
{
	int ind;

	for (ind = 0; av[ind] != NULL; ind++)
	{
		printf("%s\n", av[ind]);
	}
	return (0);
}
