/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:16:43 by phhofman          #+#    #+#             */
/*   Updated: 2024/12/09 18:43:03 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	run(int pipe_fd[2], char *cmd_pathname, char *cmd_args[], int file_fd);

void	child(int pipe_fd[2], int file_fd, char *cmd, char *envp[])
{
	char	**cmd_args;
	char	*cmd_pathname;

	close(pipe_fd[0]);
	
	cmd_args = create_cmd_args(cmd);
	if (access(cmd_args[0], X_OK) != 0)
		handle_error("Invalid Command");
	cmd_pathname = get_cmd_pathname(cmd_args[0], envp);
	run(pipe_fd, cmd_pathname, cmd_args, file_fd);
	close(pipe_fd[1]);
}
static void	run(int pipe_fd[2], char *cmd_pathname, char *cmd_args[], int file_fd)
{
	dup2(file_fd, STDIN_FILENO);
	close(file_fd);
	dup2(pipe_fd[1], STDOUT_FILENO);
	execve(cmd_pathname, cmd_args, NULL);
	handle_error("Execve failed");
}
