/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:41:29 by mstiedl           #+#    #+#             */
/*   Updated: 2023/03/30 10:16:44 by mstiedl          ###   ########.fr       */
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

void    bad_cmd_bonus(int *fd, int file, char **cmd, char *path)
{
    ft_putstr_fd("Invalid command: ", 2);
    ft_putendl_fd(cmd[0], 2);
    if (file != 0)
        close(file);
    close(fd[0]);
    close(fd[1]);
    free_split(cmd);
    free(path);
    exit(0);
}