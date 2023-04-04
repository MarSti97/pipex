/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 09:51:43 by mstiedl           #+#    #+#             */
/*   Updated: 2023/04/04 15:33:39 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_strjoin_mod(char *str1, char *str2, int pos);

void	here_doc(int ac, char **av, char **envp)
{
	char	*buffer;
	char	*limiter;
	char	*data;
	int		file[2];
	int		i;

	i = 2;
	data = NULL;
	limiter = ft_strjoin(av[2], "\n");
	while (1)
	{
		ft_printf("pipex here_doc> ");
		buffer = get_next_line(STDIN_FILENO);
		if (ft_strncmp(buffer, limiter, ft_strlen(limiter)) == 0)
			break ;
		data = ft_strjoin_mod(data, buffer, 0);
		free(buffer);
	}
	free (buffer);
	free (limiter);
	open_files(av, file, ac, data);
	while (++i < (ac - 2))
		children(av[i], envp, file);
	parent(av[i], envp, file);
}

int	make_data_fd(char *data)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		error("Error (pipe): ", 0);
	pid = fork();
	if (pid == -1)
		error("Error (fork): ", 0);
	else if (pid == 0)
	{
		close(fd[0]);
		ft_putstr_fd(data, fd[1]);
		free(data);
		exit(0);
	}
	else
	{
		close(fd[1]);
		waitpid(pid, NULL, 0);
		return (fd[0]);
	}
	return (0);
}

static char	*ft_strjoin_mod(char *str1, char *str2, int pos)
{
	size_t	len;
	char	*res;
	int		i;

	i = 0;
	len = (ft_strlen(str1 + pos) + ft_strlen(str2));
	if (len == 0)
	{
		free (str1);
		return (NULL);
	}
	res = ft_calloc(sizeof(char), (len + 1));
	if (!res)
		return (NULL);
	if (str1)
	{
		while (str1[pos])
			res[i++] = str1[pos++];
		free (str1);
	}
	pos = -1;
	if (str2)
		while (str2[++pos])
			res[i + pos] = str2[pos];
	return (res);
}
