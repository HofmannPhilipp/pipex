/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 18:27:13 by phhofman          #+#    #+#             */
/*   Updated: 2024/12/20 16:08:39 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(char *args[], char *envp[])
{
	int		end[2];
	pid_t	pid;
	// int		status;
	
	if (pipe(end) == -1)
		handle_error("Pipe failed");
	pid = fork();
	if (pid < 0)
		handle_error("Fork failed");
	if (pid == 0)
		child(end, args, envp);
	else
	{
		// if (waitpid(pid, &status, 0) == -1)
		// 	handle_error("Waitpid failed");
		// if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		// {
		// 	exit(EXIT_FAILURE);
		// }
		wait(NULL);
		parent(end, args, envp);
	}
}
