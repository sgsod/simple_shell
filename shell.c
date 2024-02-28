#include "main.h"
int handle_args(char *line, char **av);
/**
  * main - Open a simple shell
  * Return - 0 success
  */
int main(__attribute__((unused)) int ac, char **av)
{
	char *line = NULL;
	size_t n = 0;

	printf("($) ");
	while (getline(&line, &n, stdin) != EOF)
	{
		handle_args(line, av);
		printf("($) ");
	}
	printf("\n");
	return (0);
}

/**
  * handle_args - process arguments given
  * @line: string recieved from getline
  * @n: number of characters
  * Return: -1 error, 0 success
  */
int handle_args(char *line, char **av)
{
	pid_t child_p;
	int status, arg_iter;
	char *argv[2];

	argv[0] = line;
	argv[1] = NULL;
	child_p = fork();
	if (child_p == -1)
	{
		perror("Encountered problem:");
		return (-1);
	}
	if (child_p == 0)
	{
		arg_iter = strlen(line);
		if (line[arg_iter - 1] == '\n')
			line[arg_iter - 1] = '\0';
		if (execve(argv[0], argv, NULL) == -1)
		{
			perror(av[0]);
			exit(EXIT_FAILURE);
		}
	}
	else 
		wait(&status);
	return (0);
}
