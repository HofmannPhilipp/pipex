/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:16:43 by phhofman          #+#    #+#             */
/*   Updated: 2024/12/20 16:39:17 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	run(int end[2], char *cmd_path, char *cmd_args[], int fd);

void	child(int end[2],char *argv[], char *envp[])
{
	int		fd;
	char	*cmd_path;
	char	**cmd_args;

	close(end[0]);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		handle_error("Open Infile failed");
	cmd_args = create_cmd_args(argv[2]);
	cmd_path = get_cmd_path(cmd_args[0], envp);
	if (cmd_path == NULL)
		handle_error("No path found");
	run(end, cmd_path, cmd_args, fd);
	free_split(cmd_args);
	free(cmd_path);
	close(end[1]);
}
static void	run(int end[2],char *cmd_path, char *cmd_args[], int fd)
{
	dup2(fd, STDIN_FILENO);
	close(fd);
	dup2(end[1], STDOUT_FILENO);
	if (execve(cmd_path, cmd_args, NULL) == -1)
	{
		free_split(cmd_args);
		free(cmd_path);
		handle_error("Execve failed");
	}
}
