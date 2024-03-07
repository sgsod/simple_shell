#include "main.h"
char **alloc_strarr(char *line);
void c_sighandler(__attribute__((unused)) int num);
char *line = NULL;
/**
  * main - Open a simple shell
  * @ac: number of arguments
  * @av: arguments
  * Return: 0 success
  */
int main(__attribute__((unused)) int ac, char **av)
{
	size_t n = 0;
	ssize_t getline_err;

	signal(SIGINT, c_sighandler);
	if (!(isatty(fileno(stdin))))
	{ /*in case pipe '|' was used for input*/
		while ((getline_err = getline(&line, &n, stdin)) != EOF)
		{
			handle_args(line, av);
			free(line);
			line = NULL;
		}
	}
	else
	{
		printf("#cisfun$ ");
		while ((getline_err = getline(&line, &n, stdin)) != EOF)
		{
			handle_args(line, av);
			free(line);
			line = NULL;
			printf("#cisfun$ ");
		}
		putchar('\n');
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
	int status;
	char **argv;

	argv = alloc_strarr(line);

	child_p = fork();
	if (child_p == -1)
	{
		perror("Encountered problem:");
		return (-1);
	}
	if (child_p == 0)
	{
		if (execve(argv[0], argv, environ) == -1)
		{
			free(argv);
			free(line);
			perror(av[0]);
			_exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
		free(argv);
	}
	return (0);
}

/**
  * c_sighandler - handle ctrl c signal
  * @num: signal value
  */
void c_sighandler(__attribute__((unused)) int num)
{
	putchar('\n');
	free(line);
	exit(EXIT_FAILURE);
}
/**
  * alloc_strarr - create array got of argumrnts
  * @line: string to separate
  * Return: pointer to list of strings
  */
char **alloc_strarr(char *str)
{
	char **argv;
	int index, arg_len = 0, str_len = strlen(line);

	for (index = 0; str[index] != '\0'; ++index)
	{ /*tokenize line*/
		if (str[index] == ' ' || str[index] == '\n')
			str[index] = '\0';
		if ((index == 0 && str[index] != '\0')
				|| (line[index] != '\0' && line[index - 1] == '\0'))
			++arg_len;
	}
	
	argv = malloc(++arg_len * sizeof(char *));
	if (argv == NULL)
	{
		perror("Malloc -> argv");
		_exit(EXIT_FAILURE);
	}

	arg_len = 0;
	for (index = 0; index < str_len; ++index)
	{ /*make list of arguments*/
		if ((index == 0 && line[index] != '\0')
				|| (line[index] != '\0' && line[index - 1] == '\0'))
		{
			argv[arg_len] = line + index;
			++arg_len;
		}
	}
	argv[arg_len] = NULL;

	return (argv);
}
