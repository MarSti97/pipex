/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:14:59 by mstiedl           #+#    #+#             */
/*   Updated: 2023/04/04 15:40:17 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	int	files[2];
	int	i;

	i = 1;
	if (ac > 4)
	{
		if (ft_strncmp("here_doc", av[1], 9) == 0)
		{
			if (ac > 5)
				here_doc(ac, av, envp);
			else
				error("Input required: ", 1);
		}
		else
		{
			open_files(av, files, ac, NULL);
			while (++i < (ac - 2))
				children(av[i], envp, files);
			parent(av[i], envp, files);
		}
	}
	else
		error("Input required: ", 2);
	return (0);
}

void	children(char *av, char **envp, int *file)
{
	int		pipe_fds[2];
	pid_t	pid;

	if (pipe(pipe_fds) == -1)
		error("Error (pipe): ", 0);
	pid = fork();
	if (pid == -1)
		error("Error (fork): ", 0);
	else if (pid == 0)
	{
		dup2(file[0], STDIN_FILENO);
		dup2(pipe_fds[1], STDOUT_FILENO);
		close(pipe_fds[0]);
		execute(av, envp, file);
	}
	else
	{
		close(file[0]);
		close(pipe_fds[1]);
		file[0] = pipe_fds[0];
		waitpid(pid, NULL, 0);
	}
}

void	parent(char *av, char **envp, int *files)
{
	char	*path;
	char	**cmd;

	cmd = ft_split(av, 32);
	dup2(files[0], STDIN_FILENO);
	dup2(files[1], STDOUT_FILENO);
	path = find_path(cmd[0], envp, -1, -1);
	if (!path)
		bad_cmd(files, cmd, path);
	execve(path, cmd, envp);
}

void	execute(char *av, char **envp, int *files)
{
	char	*path;
	char	**cmd;

	cmd = ft_split(av, 32);
	path = find_path(cmd[0], envp, -1, -1);
	if (!path)
		bad_cmd(files, cmd, path);
	execve(path, cmd, envp);
}
