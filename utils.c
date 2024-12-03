/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:20:23 by phhofman          #+#    #+#             */
/*   Updated: 2024/12/03 14:20:44 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

// first element must be shell command and all elements after must be flags
char	**create_cmd(char *args)
{
	char **cmd;

	cmd = ft_split(args, ' ');
	if (cmd == NULL)
	{
		perror("create cmd");
		exit(EXIT_FAILURE);
	}
	return (cmd);
}