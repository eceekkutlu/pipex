#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft/libft.h"
#include <sys/wait.h>

char **get_path_line(char **envp);
char *run_cmd_path(char **path, char *cmd);
void free_double_pointer(char **av);
void file_error(int file,int *fd, int flag);

#endif
