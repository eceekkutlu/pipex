#include "pipex.h"

char **get_path_line(char **envp)
{
    int i;
    char *split_line;

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

//char *control_cmd(char *cmd)
//{
//    if(!ft_strchr(cmd,'/'))
//        return(NULL);
//    if(access(cmd,X_OK)==0)
//        return (cmd);
//    return (NULL);
//}
char *run_cmd_path(char **path, char *cmd)
{
    char *real;
    int i;
    char *full_path;

    i = 0;    
    while(path[i])
    {
        if(!(real = ft_strjoin(path[i],"/")))
            return (NULL);
        if(!(full_path = ft_strjoin(real,cmd)))
        {
            free(real);
            return (NULL);
        }
        free(real);
        if(access(full_path,F_OK |X_OK)==0)
            return (full_path);
        free(full_path);
        i++;
    }
    return (NULL);
}
