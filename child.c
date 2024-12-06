/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:16:43 by phhofman          #+#    #+#             */
/*   Updated: 2024/12/06 11:14:50 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	run(int pipe_fd[2], char *cmd_pathname, char *cmd_args[], char *filename);

void	child(int pipe_fd[2], char *infile, char *cmd, char *envp[])
{
	char	**cmd_args;
	char	*cmd_pathname;
	int		fd_infile;

	close(pipe_fd[0]);
	
	cmd_args = create_cmd_args(cmd);
	cmd_pathname = get_cmd_pathname(cmd_args[0], envp);
	run(pipe_fd, cmd_pathname, cmd_args, infile);
	close(pipe_fd[1]);
}
void	run(int pipe_fd[2], char *cmd_pathname, char *cmd_args[], char *filename)
{
	int	fd;
	
	if (access(filename, R_OK) != 0)
		handle_error("Read access failed: ");
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		handle_error("Infile open failed: ");
	dup2(fd, STDIN_FILENO);
	close(fd);
	dup2(pipe_fd[1], STDOUT_FILENO);
	execve(cmd_pathname, cmd_args, NULL);
	handle_error("Execve failed: ");
}
