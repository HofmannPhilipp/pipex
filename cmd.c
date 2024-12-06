/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:10:15 by phhofman          #+#    #+#             */
/*   Updated: 2024/12/06 10:47:44 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// first element must be shell command and all elements after must be flags
char	**create_cmd_args(char *args)
{
	char **cmd_args;

	cmd_args = ft_split(args, ' ');
	if (cmd_args == NULL)
	{
		perror("create cm_args failed");
		exit(EXIT_FAILURE);
	}
	return (cmd_args);
}

char *get_cmd_pathname(char *cmd, char *envp[])
{
	char	*pathname = "";
	char	*args[] = {"which", cmd, NULL};
	int fd[2];
	pid_t pid;

	if (pipe(fd) == -1)
		handle_error("Pipe failed: ");
	pid = fork();
	if (pid < 0)
		handle_error("Fork failed: ");
	if(pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execve("/usr/bin/which", args, envp);
		handle_error("Execve failed: ");
	}
	else
	{
		close(fd[1]);
		char buffer[256];
		int bytes_read;
		bytes_read = 0;
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

