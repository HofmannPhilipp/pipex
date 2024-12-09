/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:10:15 by phhofman          #+#    #+#             */
/*   Updated: 2024/12/06 12:40:25 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*my_read(int fd)
{
	char	buffer[256];
	char	*res;
	char	*temp;
	int		bytes_read;

	bytes_read = 0;
	res = ft_strdup("");
	if (!res)
		handle_error("Malloc failed");
	while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0)
	{
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(res, buffer);
		free(res);
		if (!temp)
			handle_error("Malloc failed");
		res = temp;
	}
	if (bytes_read == -1)
	{
		free(res);
		handle_error("Read failed");
	}
	return (res);
}
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
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		handle_error("Pipe failed");
	pid = fork();
	if (pid < 0)
		handle_error("Fork failed");
	if(pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execve("/usr/bin/which", args, envp);
		handle_error("Execve failed");
	}
	else
	{
		close(fd[1]);
		wait(NULL);
		pathname = my_read(fd[0]);
		pathname = ft_strtrim(pathname, "\n \t");
		close(fd[0]);
	}
	return (pathname);
}

