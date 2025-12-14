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

static void	execute_cmd(char *cmd, char **envp)
{
    char	**argv;
    char	*bin;

    argv = ft_split(cmd, ' ');
    if (!argv || !argv[0])
    {
        if (argv)
            free(argv);
        ft_putendl_fd("Error: empty command", 2);
        exit(127);
    }
    bin = resolve_cmd(argv[0], envp);
    if (!bin)
    {
        ft_putstr_fd("command not found: ", 2);
        ft_putendl_fd(argv[0], 2);
        free_double_pointer(argv);
        exit(127);
    }
    execve(bin, argv, envp);
    free_double_pointer(argv);
    if (bin != argv[0])
        free(bin);
    perror("execve");
    exit(127);
}

static pid_t	child_process1(int infile, int *fd, char **av, char **envp)
{
    pid_t	pid;

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
        execute_cmd(av[2], envp);
    }
    return (pid);
}

static pid_t	child_process2(int outfile, int *fd, char **av, char **envp)
{
    pid_t	pid;

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
        execute_cmd(av[3], envp);
    }
    return (pid);
}

int	main(int ac, char **av, char **envp)
{
    int		fd[2];
    int		infile;
    int		outfile;
    int		status;

    if (ac_error(ac))
        return (1);
    if (pipe(fd) == -1)
        return (perror("pipe"), 1);
    infile = open(av[1], O_RDONLY, 0777);
    if (infile < 0)
        perror(av[1]);
    outfile = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (outfile < 0)
        perror(av[4]);
    child_process1(infile, fd, av, envp);
    if (infile >= 0)
        close(infile);
    close(fd[1]);
    child_process2(outfile, fd, av, envp);
    if (outfile >= 0)
        close(outfile);
    close(fd[0]);
    waitpid(-1, NULL, 0);
    waitpid(-1, &status, 0);
    return (WIFEXITED(status) ? WEXITSTATUS(status) : 1);
}
