/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 18:27:13 by phhofman          #+#    #+#             */
/*   Updated: 2025/01/29 15:04:39 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(char *args[], char *envp[])
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;

	if (pipe(pipe_fd) == -1)
		handle_error(NULL, EXIT_FAILURE);
	pid = fork();
	if (pid < 0)
		handle_error(NULL, EXIT_FAILURE);
	if (pid == 0)
		child(pipe_fd, args, envp);
	else
	{
		parent(pipe_fd, args, envp);
		waitpid(pid, &status, 0);
	}
}
