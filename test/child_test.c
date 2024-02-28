#include "main.h"
int main (void)
{
	pid_t child_process;
	int status, count = 5;
	char *arg[] = {"/usr/bin/ls", "-l", "/home/sgsod/simple_shell", NULL};

	while (count-- > 0)
	{
		child_process = fork();
		if (child_process == -1)
		{
			perror("We have a problem:");
			return (1);
		}
		if (child_process == 0)
		{
			printf("%d\n", getpid());
			execve(arg[0], arg, NULL);
		}
		else 
			wait(&status);
	}
	return (0);
}
