/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:31:20 by phhofman          #+#    #+#             */
/*   Updated: 2024/12/20 16:03:06 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	run(char *cmd_pathname, char *cmd_args[], int fd);

void	parent(int end[2],char *argv[], char *envp[])
{
	int		fd;
	char	*cmd_path;
	char	**cmd_args;

	close(end[1]);
	dup2(end[0],STDIN_FILENO);
	close(end[0]);
	cmd_args = create_cmd_args(argv[3]);
	cmd_path = get_cmd_path(argv[3], envp);
	fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
		handle_error("Open Outfile failed");
	run(cmd_path, cmd_args, fd);
}

static void	run(char *cmd_path, char *cmd_args[], int fd)
{
	dup2(fd, STDOUT_FILENO);
	close(fd);
	execve(cmd_path, cmd_args, NULL);
	handle_error("Excecve failed");
}
