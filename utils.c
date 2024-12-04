/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:20:23 by phhofman          #+#    #+#             */
/*   Updated: 2024/12/04 16:06:25 by phhofman         ###   ########.fr       */
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
char	**create_cmd_args(char *args, char *filename)
{
	char **cmd;

	char *cmd_args = ft_strjoin(args, " ");
	cmd_args = ft_strjoin(cmd_args, filename);
	cmd = ft_split(cmd_args, ' ');
	if (cmd == NULL)
	{
		perror("create cmd");
		exit(EXIT_FAILURE);
	}
	return (cmd);
}

char *get_cmd_pathname(char *cmd, char *envp[])
{
	char	*pathname = "";
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
			pathname = ft_strjoin(pathname, buffer);
		}
		pathname = ft_strtrim(pathname, "\n \t");
		close(fd[0]);
	}
	return (pathname);
}

void	run_cmd(char *cmd_pathname, char *cmd_args[])
{
	int fd[2];
	pid_t pid;

	pipe(fd);
	pid = fork();
	// char *args[] = {"wc", "-l", "infile.txt", NULL};
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		
		execve(cmd_pathname, cmd_args, NULL);
		perror("execve run_cmd");
	}
	else
	{
		char	buffer[256];
		int		bytes_read;
		char	*res = "";

		bytes_read = 0;
		close(fd[1]);
		wait(NULL);
		while ((bytes_read = read(fd[0], buffer, sizeof(buffer) - 1)) > 0)
		{	
			buffer[bytes_read] = '\0';
			res = ft_strjoin(res, buffer);
		}
		printf("%s",res);
		close(fd[0]);
	}
}