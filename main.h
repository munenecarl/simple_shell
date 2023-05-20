#ifndef MAIN_H
#define MAIN_H
#define BUFSIZE 1024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdint.h>


extern char **environ;
typedef long int ssize_t;


int executor(char **tokens);
char *path_finder(char *cmd);
ssize_t _getline(char **pline_buf, size_t *pn, FILE *fin);
void free_tokens(char **tokens);


#endif
