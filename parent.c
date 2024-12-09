/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:31:20 by phhofman          #+#    #+#             */
/*   Updated: 2024/12/09 18:45:12 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	run(char *cmd_pathname, char *cmd_args[], int file_fd);

void	parent(int pipe_fd[2], int file_fd, char *cmd, char *envp[])
{
	char **cmd_args;
	char *cmd_pathname;
	
	close(pipe_fd[1]);
	wait(NULL);
	dup2(pipe_fd[0],STDIN_FILENO);
	close(pipe_fd[0]);
	cmd_args = create_cmd_args(cmd);
	if (access(cmd_args[0], X_OK) != 0)
		handle_error("Invalid Command");
	cmd_pathname = get_cmd_pathname(cmd_args[0], envp);
	run(cmd_pathname, cmd_args, file_fd);
}

static void	run(char *cmd_pathname, char *cmd_args[], int file_fd)
{
	dup2(file_fd, STDOUT_FILENO);
	close(file_fd);
	execve(cmd_pathname, cmd_args, NULL);
	handle_error("Excecve failed");
}
