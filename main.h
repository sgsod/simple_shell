#ifndef MAIN_H
#define MAIN_H
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
extern char **environ;
int handle_args(char *line, char **av);
#endif /* MAIN_H */
