/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:20:23 by phhofman          #+#    #+#             */
/*   Updated: 2024/12/09 16:28:05 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_fd(int fd)
{
	char	buffer[256];
	int		bytes_read;
	char	*res = "";
	
	while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0)
	{	
		buffer[bytes_read] = '\0';
		res = ft_strjoin(res, buffer);
	}
	ft_printf("%s",res);
}

void	print_cmd(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != NULL)
	{
		ft_printf("%s ", cmd[i]);
		i++;
	}
	ft_printf("\n");
}

void	handle_error(char *error_msg)
{
	if (!error_msg)
		perror(NULL);
	else
		fprintf(stderr, "%s: %s\n",error_msg, strerror(errno));
	exit(EXIT_FAILURE);
}
