#include <stdio.h>
#include "pipex.h"
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
// cat main.c | wc -l

static char *resolve_cmd(char *cmd, char **envp)
{
    char **paths;
    char *full;

    if (access(cmd, X_OK) == 0)
        return cmd;
    paths = get_path_line(envp);
    if (!paths)
        return NULL;
    full = run_cmd_path(paths, cmd); // uses pipex_path.c
    // free paths array
    for (int i = 0; paths[i]; i++) free(paths[i]);
    free(paths);
    return full;
}

static void child_process(int infile, int *fd, char **av, char **envp)
{
    int i;

    i= 0;
    int pid = fork();
    if (pid < 0)
        perror("fork");
    if (pid == 0)
    {
        close(fd[0]);
        if (dup2(infile, STDIN_FILENO) == -1 || dup2(fd[1], STDOUT_FILENO) == -1)
            perror("dup2");
        close(fd[1]);
        close(infile);
        // av[2] is cmd1; split by space for argv
        char **argv1 = ft_split(av[2], ' ');
        if (!argv1) exit(1);
        char *bin = resolve_cmd(argv1[0], envp);
        if (!bin)
        {
            while (argv1[i])
            {
                free(argv1[i]);
                i++;
            }
            free(argv1);
        }
        if(execve(bin, argv1, envp) != -1)
        {
            exit(1);
        }
        perror("execve cmd1");
        exit(127);
    }
}

int main(int ac, char **av, char **envp)
{
    if (ac == 5)
    {
        int i;

        i = 0;
		int fd[2];
		pipe(fd);
		int infile = open(av[1], O_RDONLY, 0777);
		int outfile = open(av[4], O_CREAT | O_RDWR| O_TRUNC, 0777);
        child_process(infile, fd, av, envp);
		close(fd[1]);
		dup2(fd[0],STDIN_FILENO);
		dup2(outfile, 1);
       char **argv2 = ft_split(av[3], ' ');
        if (!argv2)
             exit(1);
        char *bin2 = resolve_cmd(argv2[0], envp);
        while (argv2[i])
        {
            free(argv2[i]);
            i++;
        }
        free(argv2);
        execve(bin2, argv2, envp);		
        close(fd[0]);
		close(outfile);
		wait(NULL);
		close(fd[0]);
    }
    return (0);
}
