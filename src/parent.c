/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:31:20 by phhofman          #+#    #+#             */
/*   Updated: 2025/01/29 16:30:27 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	redirect(int fd, int pipe_fd[2]);

void	parent(int pipe_fd[2], char *argv[], char *envp[])
{
	char	*cmd_path;
	char	**cmd_args;
	int		fd;

	close(pipe_fd[1]);
	fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		handle_error(NULL, EXIT_FAILURE);
	cmd_args = create_cmd_args(argv[3]);
	if (!cmd_args)
		handle_error(NULL, EXIT_FAILURE);
	cmd_path = get_cmd_path(cmd_args[0], envp);
	if (!cmd_path)
	{
		free_split(cmd_args);
		handle_error("command not found", 127);
	}
	if (redirect(fd, pipe_fd) == EXIT_FAILURE)
		handle_error(NULL, EXIT_FAILURE);
	execve(cmd_path, cmd_args, envp);
	free_split(cmd_args);
	free(cmd_path);
	handle_error(NULL, EXIT_FAILURE);
}

static int	redirect(int fd, int pipe_fd[2])
{
	if (dup2(pipe_fd[0], STDIN_FILENO) < 0)
		return (EXIT_FAILURE);
	close(pipe_fd[0]);
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (EXIT_FAILURE);
	close(fd);
	return (EXIT_SUCCESS);
}
