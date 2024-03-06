#include "main.h"
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
		for (; line[arg_iter] == '\n' || line[arg_iter] == ' '; --arg_iter)
			line[arg_iter] = '\0';


		if (execve(argv[0], argv, environ) == -1)
		{
			free(line);
			perror(av[0]);
			_exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
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
  * line string to separate
  * argv = alloc_strarr(line);
  * return pointer to line
  *
  * char **alloc_strarr(char *line)
  * {
  * char **argv;
  * int index, arg_len = 0, st;
  * for (index = 0; line[index] != '\0'; ++index)
  * {
  * if ((index == 0 && line[index] != ' ')
  * || (line[index] != ' ' && str[index - 1] == '\0'))
  * arg_len++;
  * if (line[index] == ' ' || line[index] == '\n')
  * line[index] = '\0';
  * }
  * }
  */
