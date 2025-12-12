#include "pipex.h"
static char	*resolve_cmd(char *cmd, char **envp)
{
    char	**paths;
    char	*full;
    int		i;

    if (!cmd || !cmd[0])
        return (NULL);
    if (access(cmd, X_OK) == 0)
        return (cmd);
    paths = get_path_line(envp);
    if (!paths)
        return (NULL);
    full = run_cmd_path(paths, cmd);
    i = 0;
    while (paths[i])
    {
        free(paths[i]);
        i++;
    }
    free(paths);
    return (full);
}

static pid_t	child_process1(int infile, int *fd, char **av, char **envp)
{
    pid_t	pid;
    char	**argv1;
    char	*bin;

    pid = fork();
    if (pid < 0)
        perror("fork");
    if (pid == 0)
    {
        close(fd[0]);
        if (dup2(infile, STDIN_FILENO) == -1
            || dup2(fd[1], STDOUT_FILENO) == -1)
            perror("dup2");
        close(fd[1]);
        close(infile);
        argv1 = ft_split(av[2], ' ');
        if (!argv1 || !argv1[0])
        {
            if (argv1)
                free(argv1);
            ft_putendl_fd("Error: empty command", 2);
            exit(127);
        }
        bin = resolve_cmd(argv1[0], envp);
        if (!bin)
        {
            ft_putstr_fd("command not found: ", 2);
            ft_putendl_fd(argv1[0], 2);
            free_double_pointer(argv1);
            exit(127);
        }
        execve(bin, argv1, envp);
        free_double_pointer(argv1);
        if (bin != argv1[0])
            free(bin);
        perror("execve cmd1");
        exit(127);
    }
    return (pid);
}

static pid_t	child_process2(int outfile, int *fd, char **av, char **envp)
{
    pid_t	pid;
    char	**argv2;
    char	*bin2;

    pid = fork();
    if (pid < 0)
        perror("fork");
    if (pid == 0)
    {
        close(fd[1]);
        if (dup2(fd[0], STDIN_FILENO) == -1
            || dup2(outfile, STDOUT_FILENO) == -1)
            perror("dup2");
        close(fd[0]);
        close(outfile);
        argv2 = ft_split(av[3], ' ');
        if (!argv2 || !argv2[0])

        {
            if (argv2)
                free(argv2);
            ft_putendl_fd("Error: empty command", 2);
            exit(127);
        }
        bin2 = resolve_cmd(argv2[0], envp);
        if (!bin2)
        {
            ft_putstr_fd("command not found: ", 2);
            ft_putendl_fd(argv2[0], 2);
            free_double_pointer(argv2);
            exit(127);
        }
        execve(bin2, argv2, envp);
        free_double_pointer(argv2);
        if (bin2 != argv2[0])
            free(bin2);
        perror("execve cmd2");
        exit(127);
    }
    return (pid);
}

int	main(int ac, char **av, char **envp)
{
    int		fd[2];
    int		infile;
    int		outfile;
    pid_t	pid1;
    pid_t	pid2;
    int		status;

    if (ac != 5)
    {
        ft_putendl_fd("Usage: ./pipex infile cmd1 cmd2 outfile", 2);
        return (1);
    }
    if (pipe(fd) == -1)
    {
        perror("pipe");
        return (1);
    }
    infile = open(av[1], O_RDONLY, 0777);
    if (infile < 0)
        perror(av[1]);
    outfile = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (outfile < 0)
        perror(av[4]); 
    pid1 = child_process1(infile, fd, av, envp);
    if (infile >= 0)
        close(infile);
    close(fd[1]);
    
    pid2 = child_process2(outfile, fd, av, envp);
    if (outfile >= 0)
        close(outfile);
    close(fd[0]);
    
    waitpid(pid1, NULL, 0);
    waitpid(pid2, &status, 0);
    
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    return (1);
}
