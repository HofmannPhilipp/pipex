/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:16:43 by phhofman          #+#    #+#             */
/*   Updated: 2024/12/04 11:13:08 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child(int pipe_fd[2], const char *infile, char **cmd)
{
	int	fd;
	char buffer[256];
	char *file;
	int bytes_read;

	close(pipe_fd[0]);
	fd = open(infile, O_RDONLY);
	if (fd < 0 || access(infile, R_OK) == -1)
	{
		perror("open file 1");
		exit(EXIT_FAILURE);
	}
	while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0)
	{	
		buffer[bytes_read] = '\0';
		ft_strjoin(file, buffer);
	}
	
	close(pipe_fd[1]);
}