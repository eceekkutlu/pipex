#include <stdio.h>
#include "pipex.h"

int main(int ac, char **av, char **envp)
{
    
    if(ac == 5)
    {
        int fd[2];
        int infile = open(av[1],O,0777);
        //hata
        int outfile = open(av[4],O,0777);
        //hata
        pipe(fd);
        int child1 = fork();
        if(a == 0)
        {
            close(fd[0]);
            dup2(in,0);
            dup2(fd[1],STDOUT_FİLENO);
            execve()
        }
        int b = fork();
        if(b == 0)
        {
            close(fd[1]);
            dup2(fd[0],STDİN_FİLENO);
            dup2(out,1);
        }
    }
}
int  child()
    {
        int a = fork();
        if(a == 0)
        {
            close(fd[0]);
            dup2(in,0);
            dup2(fd[1],STDOUT_FİLENO);
            execve()
        }
    }
   