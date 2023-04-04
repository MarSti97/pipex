/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 13:42:46 by mstiedl           #+#    #+#             */
/*   Updated: 2023/04/04 15:39:59 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>

void	children(char *av, char **envp, int *file);
void	parent(char *av, char **envp, int *files);
void	execute(char *av, char **envp, int *files);
//tools
void	error(char *msg, int arg);
void	free_split(char **split);
void	bad_cmd(int *files, char **cmd, char *path);
char	*find_path(char *cmd, char **envp, int i, int j);
void	open_files(char **av, int *fds, int ac, char *data);
// here_doc
void	here_doc(int ac, char **av, char **envp);
int		make_data_fd(char *data);

#endif