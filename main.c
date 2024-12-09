/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:02:11 by phhofman          #+#    #+#             */
/*   Updated: 2024/12/09 18:48:02 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


int	main(int argc, char *argv[], char *envp[])
{
	if (argc != 5)
	{
		ft_printf("Usage: %s infile cmd1 cmd2 outfile\n", argv[0]);
		handle_error("Invalid number of arguments");
	}
	int		pipe_fd[2];
	pid_t	pid;
	int		infile_fd;
	int		outfile_fd;
	int		status;

	infile_fd = open(argv[1], O_RDONLY);
	outfile_fd = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (infile_fd < 0 || outfile_fd < 0)
		handle_error("Open file failed");
	if (pipe(pipe_fd) == -1)
		handle_error("Pipe failed");
	pid = fork();
	if (pid < 0)
		handle_error("Fork failed");
	if (pid == 0)
		child(pipe_fd, infile_fd, argv[2], envp);
	else
	{
		if (waitpid(pid, &status, 0) == -1)
			handle_error("Waitpid failed");
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		{
			exit(EXIT_FAILURE);
		}
		parent(pipe_fd, outfile_fd, argv[3], envp);
	}
	exit(EXIT_SUCCESS);
}
