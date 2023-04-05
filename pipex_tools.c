/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:41:29 by mstiedl           #+#    #+#             */
/*   Updated: 2023/04/05 10:05:34 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(char *msg, int arg)
{
	if (arg == 0)
		perror(msg);
	else if (arg == 1)
	{
		ft_putstr_fd(msg, 2);
		ft_putendl_fd("here_doc <LIMITER> <cmd1> <cdm2> <outfile>", 2);
	}
	else
	{
		ft_putstr_fd(msg, 2);
		ft_putendl_fd("<infile> <command1> <command2> <outfile>", 2);
	}
	exit(EXIT_FAILURE);
}

void	free_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

void	bad_cmd(int *files, char **cmd, char *path)
{
	ft_putstr_fd("Invalid command: ", 2);
	ft_putendl_fd(cmd[0], 2);
	close(files[0]);
	close(files[1]);
	free_split(cmd);
	free(path);
	exit(EXIT_FAILURE);
}

char	*find_path(char *cmd, char **envp, int i, int j)
{
	char	**paths;
	char	*the_path;

	cmd = ft_strjoin("/", cmd);
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
		{
			paths = ft_split(envp[i] + 5, ':');
			while (paths[++j])
			{
				the_path = ft_strjoin(paths[j], cmd);
				if (access(the_path, F_OK) == 0)
				{
					free_split(paths);
					free(cmd);
					return (the_path);
				}
				free (the_path);
			}
			free (cmd);
		}
	}
	return (NULL);
}

void	open_files(char **av, int *fds, int ac, char *data)
{
	if (data == NULL)
	{
		fds[0] = open(av[1], O_RDONLY);
		if (fds[0] < 0)
			error("Error (infile)", 0);
		fds[1] = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fds[1] < 0)
			error("Error (outfile)", 0);
	}
	else
	{
		fds[1] = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fds[1] < 0)
			error("Error (outfile)", 0);
		fds[0] = make_data_fd(data);
	}
}
