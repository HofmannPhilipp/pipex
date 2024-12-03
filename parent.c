/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:31:20 by phhofman          #+#    #+#             */
/*   Updated: 2024/12/03 16:44:36 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parent(int pipe_fd[2], char *outfile, char *cmd)
{
	char buffer[10];
	int bytes_read;
	
	bytes_read = 0;
	close(pipe_fd[1]);
	wait(NULL);
	while ((bytes_read = read(pipe_fd[0], buffer, sizeof(buffer) - 1)) > 0)
	{	
		buffer[bytes_read] = '\0';
		ft_printf("%s", buffer);
	}
	close(pipe_fd[0]);
}