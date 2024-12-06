/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:02:11 by phhofman          #+#    #+#             */
/*   Updated: 2024/12/06 10:11:30 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


int	main(int argc, char *argv[], char *envp[])
{
	if (argc != 5)
	{
		ft_printf("Usage: %s infile cmd1 cmd2 outfile\n", argv[0]);
		handle_error("Invalid number of arguments: ");
	}

	int	pipe_fd[2];
	pid_t	pid;
	
	if (pipe(pipe_fd) == -1)
		handle_error("Pipe failed: ");
	pid = fork();
	if (pid < 0)
		handle_error("Fork failed: ");
	if (pid == 0)
		child(pipe_fd, argv[1], argv[2], envp);
	else
		parent(pipe_fd, argv[4], argv[3], envp);
}
