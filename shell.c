#include "main.h"
int handle_args(char *line, int n, char **av, char **env);
/**
  * main - Open a simple shell
  * Return - 0 success
  */
int main(int ac, char **av, char **env)
{
	char *line = NULL;
	size_t n = 0;

	printf("($) %d", getpid());
	while (getline(&line, &n, stdin) != EOF)
	{
		handle_args(line, n, av, env);
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
int handle_args(char *line, int n, char **av, char **env)
{
	pid_t child_p;
	int status, arg_iter;
	char *argv[] = {line, NULL};

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
		if (execve(argv[0], argv, env) == -1)
		{
			printf("%s\n", line);
			perror(av[0]);
			exit(EXIT_FAILURE);
		}
	}
	else 
		wait(&status);
	return (0);
}
