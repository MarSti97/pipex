/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 13:42:46 by mstiedl           #+#    #+#             */
/*   Updated: 2023/03/29 18:26:53 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include "./libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

char    *find_path(char *cmd, char **envp);
void    child(char **av, char **envp, int *fd, int *files);
void    parent(char **av, char **envp, int *fd, int *files);
//tools
void    free_split(char **split);
void    error(char *msg);
void    close_fds(int *pipe, int *files);
void    open_file(char **av, int *fds);
void    bad_cmd(int *fd, int *files, char **cmd, char *path);
//bonus
void    bad_cmd_bonus(int *fd, int file, char **cmd, char *path);
void    child_bonus(char **av, char **envp, int *fd);
void    parent_bonus(char **av, char **envp, int *fd, int last);

#endif