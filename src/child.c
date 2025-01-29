/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:16:43 by phhofman          #+#    #+#             */
/*   Updated: 2025/01/29 15:00:29 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	open_and_dup(char *file, int pipe_fd[2]);

void	child(int pipe_fd[2], char *argv[], char *envp[])
{
	char	*cmd_path;
	char	**cmd_args;

	close(pipe_fd[0]);
	cmd_args = ft_split(argv[2], ' ');
	if (!cmd_args)
		exit(EXIT_FAILURE);
	cmd_path = get_cmd_path(cmd_args[0], envp);
	if (!cmd_path)
	{
		free_split(cmd_args);
		handle_error("command not found", 127);
	}
	if (open_and_dup(argv[1], pipe_fd) == EXIT_FAILURE)
	{
		free_split(cmd_args);
		free(cmd_path);
		exit(EXIT_FAILURE);
	}
	execve(cmd_path, cmd_args, envp);
	free_split(cmd_args);
	free(cmd_path);
	exit(EXIT_FAILURE);
}

static int	open_and_dup(char *file, int pipe_fd[2])
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (EXIT_FAILURE);
	if (dup2(fd, STDIN_FILENO) < 0)
		return (EXIT_FAILURE);
	close(fd);
	if (dup2(pipe_fd[1], STDOUT_FILENO) < 0)
		return (EXIT_FAILURE);
	close(pipe_fd[1]);
	return (EXIT_SUCCESS);
}
