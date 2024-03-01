#include "main.h"
/**
  * main - Open a simple shell
  * @ac: number of arguments
  * @av: arguments
  * Return: 0 success
  */
int main(__attribute__((unused)) int ac, char **av)
{
	char *line = NULL;
	size_t n = 0;

	if (!(isatty(fileno(stdin))))
	{ /*in case pipe '|' was used for input*/
		while (getline(&line, &n, stdin) != EOF)
		{
			handle_args(line, av);
		}
		return (0);
	}

	printf("#cisfun$ ");
	while (getline(&line, &n, stdin) != EOF)
	{
		handle_args(line, av);
		printf("#cisfun$ ");
	}
	free(line);
	return (0);
}

/**
  * handle_args - process arguments given
  * @line: string recieved from getline
  * @av: number of characters
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
		arg_iter = strlen(line) - 1;
		if (line[arg_iter] == '\n')
			line[arg_iter] = '\0';

		if (execve(argv[0], argv, environ) == -1)
		{
			free(line);
			perror(av[0]);
			exit(EXIT_FAILURE);
		}
	}
	else
		wait(&status);
	return (0);
}
/**
  * alloc_strarr - create array got of argumrnts
  * line string to separate
  * argv = alloc_strarr(line);
  * return pointer to line
  */
