/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:14:59 by mstiedl           #+#    #+#             */
/*   Updated: 2023/04/03 18:36:04 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int ac, char **av, char **envp)
{
    int files[2];
    int i;

    i = 1;
    if (ac >= 4)
    {
        if (ft_strncmp("here_doc", av[1], 9) == 0)
            here_doc(ac, av, envp);
        else
        {
            open_files_bonus(av, files, ac);
            while (++i < (ac - 2))
                children(av[i], envp, files);
            parent_bonus(av[i], envp, files);    
        }
    }
    else
        error("[Incorrect input] Input required: <infile> <command1> <command2> <outfile>");
    return (0);
}

void    parent_bonus(char *av, char **envp, int *files)
{
    char    *path;
    char    **cmd;

    cmd = ft_split(av, 32);
    dup2(files[0], STDIN_FILENO);
    dup2(files[1], STDOUT_FILENO);
    path = find_path(cmd[0], envp);
    if (!path)
        bad_cmd_bonus(files, cmd, path);
    execve(path, cmd, envp);
}

void	execute(char *av, char **envp, int *files)
{
		char    *path;
    	char    **cmd;

		cmd = ft_split(av, 32);
		path = find_path(cmd[0], envp);
		if (!path)
			bad_cmd_bonus(files, cmd, path);
		execve(path, cmd, envp);
}

void	children(char *av, char **envp, int *file)
{
	int pipe_fds[2];
    pid_t pid;

	if (pipe(pipe_fds) == -1) // 0 is for reading, 1 for writing
		error("Failed to pipe");
	pid = fork();
	if (pid == -1)
		error("Failed to fork");
	else if (pid == 0)
	{
		// ft_putendl_fd("HERE", 2);
		dup2(file[0], STDIN_FILENO);	
        dup2(pipe_fds[1], STDOUT_FILENO);
        close(pipe_fds[0]);
		execute(av, envp, file);
	}
    else
    {
        // close read pipe and close infile
        close(file[0]);
        close(pipe_fds[1]);
        file[0] = pipe_fds[0];
        waitpid(pid, NULL, 0);
    }
}

void    here_doc(int ac, char **av, char **envp)
{
    char    *buffer;
    char    *limiter;
    char    *data;
    int     file[2];
    int     i;

    i = 2;
    file[1] = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644); // test the actual command see if it clears the existing file
    if (file[1] < 0)
        error("Could not open file");
    data = NULL;
    limiter = ft_strjoin(av[2], "\n");
    while (1)
    {
        ft_printf("here_doc> ");
        buffer = get_next_line(STDIN_FILENO);
        if (ft_strncmp(buffer, limiter, ft_strlen(limiter)) == 0)
            break ;
        data = ft_strjoin_mod(data, buffer, 0);
        free(buffer);
    }
    free (buffer);
    free (limiter);
    file[0] = make_data_fd(data);
    while (++i < (ac - 2))
        children(av[i], envp, file);
    parent_bonus(av[i], envp, file);
}

int make_data_fd(char *data)
{
    int fd[2];
    pid_t pid;

    if (pipe(fd) == -1)
    		error("Failed to pipe");
	pid = fork();
	if (pid == -1)
		error("Failed to fork");
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