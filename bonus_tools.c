/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:41:29 by mstiedl           #+#    #+#             */
/*   Updated: 2023/04/03 12:15:50 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    error(char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

void    free_split(char **split)
{
    int i;
    
    i = -1;
    while (split[++i])
        free(split[i]);
    free(split);
}

void    bad_cmd_bonus(int *files, char **cmd, char *path)
{
    ft_putstr_fd("Invalid command: ", 2);
    ft_putendl_fd(cmd[0], 2);
    close(files[0]);
    close(files[1]);
    free_split(cmd);
    free(path);
    exit(0);
}

char    *find_path(char *cmd, char **envp)
{
    char    **paths;
    char    *the_path;
    int     i;
    
    cmd = ft_strjoin("/", cmd);
    i = -1;
    while (envp[++i])
    {
        if (ft_strncmp(envp[i], "PATH", 4) == 0)
        {
            paths = ft_split(envp[i] + 5, ':');
            i = -1; 
            while (paths[++i])
            {
                the_path = ft_strjoin(paths[i], cmd);
                if (access(the_path, F_OK) == 0)
                {
                    free_split(paths);
                    return (the_path);
                }
                free (the_path);
            }
        }
    }
    return (NULL);
}

void    open_files_bonus(char **av, int *fds, int ac)
{
    fds[0] = open(av[1], O_RDONLY);
    if (fds[0] < 0)
        error("Failed to open infile");
    fds[1] = open(av[ac - 1], O_WRONLY);
    if (fds[1] < 0)
        error("Failed to open outfile");
}
