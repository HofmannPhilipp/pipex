/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:02:11 by phhofman          #+#    #+#             */
/*   Updated: 2024/12/03 16:40:17 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


int	main(int argc, char *argv[])
{
	if (argc != 5)
	{
		ft_putstr_fd("Error: Invalid number of arguments.\n",2);
		ft_printf("Usage: %s file1 cmd1 cmd2 file2\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	// pipe_fd[0] read
	// pipe_fd[1] write
	int	pipe_fd[2];
	const char *infile;
	const char *outfile;
	char **cmd1;
	char **cmd2;
	pid_t	pid;
	pipe(pipe_fd);
	pid = fork();
	infile = argv[1];
	outfile = argv[4];
	cmd1 = create_cmd(argv[2]);
	cmd2 = create_cmd(argv[3]);
	// child proccess
	if (pid == 0)
		child(pipe_fd, infile, cmd1);

	// parent proccess
	else
		parent(pipe_fd, outfile, cmd2);
}