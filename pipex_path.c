#include "pipex.h"

char	**get_path_line(char **envp)
{
    int		i;
    char	*split_line;

	i = 0;
	while(envp[i])
	{
		if(!ft_strncmp(envp[i],"PATH=",5))
		{
			split_line = envp[i] + 5;
			return (ft_split(split_line,':'));
		}
		i++;
	}
	return (NULL);
}

char	*run_cmd_path(char **path, char *cmd)
{
    char	*real;
    int		i;
    char	*full_path;

	if (!path || !cmd)
		return (NULL);
	i = 0;    
	while(path[i])
	{
		real = ft_strjoin(path[i],"/");
		if (!real)
			return (NULL);
		full_path = ft_strjoin(real,cmd);
		free(real);
		if (!full_path)
			return (NULL);
		if(access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}