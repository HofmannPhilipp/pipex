/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:02:11 by phhofman          #+#    #+#             */
/*   Updated: 2024/12/04 16:04:08 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


int	main(int argc, char *argv[], char *envp[])
{
	// if (argc != 5)
	// {
	// 	ft_putstr_fd("Error: Invalid number of arguments.\n",2);
	// 	ft_printf("Usage: %s file1 cmd1 cmd2 file2\n", argv[0]);
	// 	exit(EXIT_FAILURE);
	// }
	
	// pipe_fd[0] read
	// pipe_fd[1] write
	// char *arg[] = {"wc", "-l", "infile.txt", NULL};
	// execve("/usr/bin/wc", arg, envp);
	int	pipe_fd[2];
	char *infile;
	char *outfile;
	pid_t	pid;
	pipe(pipe_fd);
	pid = fork();
	infile = argv[1];
	// outfile = argv[4];
	// child proccess
	if (pid == 0)
		child(pipe_fd, infile, argv[2], envp);

	// parent proccess
	else
		parent(pipe_fd, outfile, argv[3]);
}