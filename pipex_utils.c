
#include "pipex.h"
void free_double_pointer(char **av)
{
	int i;

	i = 0;
	while (av[i])
	{
		free(av[i]);
		i++;
	}
	free(av);
}
void file_error(int file,int *fd, int flag)
{
	if (file < 0)
	{
		if(flag == 1)
		{
			perror("open outfile");
			close(file);
		}
		else if(flag == 0)
			perror("open infile");
		close(fd[0]);
		close(fd[1]);
		exit(1);
	}
}
int ac_error(int ac)
{
	if (ac != 5)
	{
		ft_putendl_fd("Usage: ./pipex infile cmd1 cmd2 outfile", 2);
		return (1);
	}
	return (0);
}