/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 13:42:46 by mstiedl           #+#    #+#             */
/*   Updated: 2023/04/03 18:26:08 by mstiedl          ###   ########.fr       */
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
void    bad_cmd_bonus(int *files, char **cmd, char *path);
void    parent_bonus(char *av, char **envp, int *files);
void    open_files_bonus(char **av, int *fds, int ac);
void	children(char *av, char **envp, int *file);
void	execute(char *av, char **envp, int *files);
void    here_doc(int ac, char **av, char **envp);
int     make_data_fd(char *data);
static char	*ft_strjoin_mod(char *str1, char *str2, int pos);

#endif