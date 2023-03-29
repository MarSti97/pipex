/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:37:02 by mstiedl           #+#    #+#             */
/*   Updated: 2023/03/29 16:47:03 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    error(char *msg)
{
    ft_putendl_fd(msg, 2);
    exit(0);
}

void    free_split(char **split)
{
    int i;
    
    i = -1;
    while (split[++i])
        free(split[i]);
    free(split);
}

void    close_fds(int *pipe, int *files)
{
    close(pipe[0]);
    close(pipe[1]);
    close(files[0]);
    close(files[1]);
}

void open_file(char **av, int *fds)
{
    fds[0] = open(av[1], O_RDONLY);
    if (fds[0] < 0)
        error("Failed to open first file");
    fds[1] = open(av[4], O_WRONLY);
    if (fds[1] < 0)
        error("Failed to open last file");
}

void    bad_cmd(int *fd, int *files, char **cmd, char *path)
{
    ft_putstr_fd("Invalid command: ", 2);
    ft_putendl_fd(cmd[0], 2);
    close_fds(fd, files);
    free_split(cmd);
    free(path);
    exit(0);
}