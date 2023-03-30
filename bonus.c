/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:14:59 by mstiedl           #+#    #+#             */
/*   Updated: 2023/03/30 13:46:10 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int ac, char **av, char **envp)
{
    int pipe_fds[2];
    int files[2];
    pid_t pid;
    int     i;

    i = 2;
    if (ac >= 5)
    {
        open_files_bonus(av, files, ac);
        dup2(files[0], STDIN_FILENO);
        if (pipe(pipe_fds) == -1) // 0 is for reading, 1 for writing
            error("Failed to pipe");
        pid = fork();
        if (pid == -1)
            error("Failed to fork");
        else if (pid == 0)
            child_bonus(av, envp, pipe_fds);
        waitpid(pid, NULL, 0);
        while (++i < (ac - 2))
            multi_pipe(av[i], envp, pipe_fds);
        // if (ac > 5)
        //     multi_pipe(av, envp, pipe_fds, ((ac - 2) - 3));
        dup2(files[1], STDOUT_FILENO);
        parent_bonus(av, envp, pipe_fds, ac);
    }
    else
        error("Incorrect input\nInput required: <infile> <command1> <command2> <outfile>");
    return (0);
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

void    child_bonus(char **av, char **envp, int *fd)
{
    char    *path;
    char    **cmd;

    cmd = ft_split(av[2], 32);
    dup2(infile, STDIN_FILENO);
    dup2(fd[1], STDOUT_FILENO);
    close(fd[0]);
    path = find_path(cmd[0], envp);
    if (!path)
        bad_cmd_bonus(fd, infile, cmd, path);
    execve(path, cmd, envp);
}

void    parent_bonus(char **av, char **envp, int *fd, int ac)
{
    char    *path;
    char    **cmd;

    cmd = ft_split(av[ac - 2], 32);
    dup2(fd[0], STDIN_FILENO);
    dup2(outfile, STDOUT_FILENO);
    close(fd[1]);
    path = find_path(cmd[0], envp);
    if (!path)
        bad_cmd_bonus(fd, outfile, cmd, path);
    execve(path, cmd, envp);
}

void    multi_pipe(char *av, char **envp, int *fd)
{
    char    *path;
    char    **cmd;
    int     temp_pipe[2];
    pid_t   pid;
    
    if (pipe(temp_pipe) == -1) // 0 is for reading, 1 for writing
        error("Failed to pipe");
    pid = fork();
    if (pid == -1)
        error("Failed to fork");
    else if (pid == 0)
    {
        cmd = ft_split(av, 32);
        dup2(fd[0], STDIN_FILENO);
        dup2(fd[1], STDOUT_FILENO);
        path = find_path(cmd[0], envp);
        if (!path)
            bad_cmd_bonus(fd, 0, cmd, path);
        execve(path, cmd, envp);
    }
    waitpid(pid, NULL, 0);    
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