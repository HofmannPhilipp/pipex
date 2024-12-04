/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:20:23 by phhofman          #+#    #+#             */
/*   Updated: 2024/12/04 11:21:21 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_cmd(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != NULL)
	{
		ft_printf("%s ", cmd[i]);
		i++;
	}
	ft_printf("\n");
}

// first element must be shell command and all elements after must be flags
char	**create_cmd(char *args)
{
	char **cmd;

	cmd = ft_split(args, ' ');
	if (cmd == NULL)
	{
		perror("create cmd");
		exit(EXIT_FAILURE);
	}
	return (cmd);
}

char *get_cmd_pathname(char *cmd, char *envp[])
{
	char	*pathname;
	char	*argv[] = {"which", cmd, NULL};
	
	int fd[2];
	pipe(fd);
	pid_t pid = fork();

	if(pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execve("/usr/bin/which", argv, envp);
		perror("execve which failed");
		exit(EXIT_FAILURE);
	}
	else
	{
		close(fd[1]);
		char buffer[256];
		int bytes_read;
		bytes_read = 0;
		int status;
		wait(NULL);
		while ((bytes_read = read(fd[0], buffer, sizeof(buffer) - 1)) > 0)
		{	
			buffer[bytes_read] = '\0';
			ft_strjoin(pathname, buffer);
		}
		close(fd[0]);
	}
	return (pathname);
}

void	run_cmd(char *cmd, char *envp[])
{
	char *pathname;
	int fd[2];
	pid_t pid;
	char **cmd_args;

	pathname = get_cmd_pathname(cmd, envp);
	cmd_args = create_cmd(cmd);
	pipe(fd);
	pid = fork();

	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execve(pathname, cmd_args, envp);
		perror("execve run_cmd");
	}
	else
	{
		close(fd[1]);
		char buffer[256];
		int bytes_read;
		bytes_read = 0;
		int status;
		wait(NULL);
		while ((bytes_read = read(fd[0], buffer, sizeof(buffer) - 1)) > 0)
		{	
			buffer[bytes_read] = '\0';
			ft_strjoin(pathname, buffer);
		}
		close(fd[0]);
	}
}