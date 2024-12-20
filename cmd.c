/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:10:15 by phhofman          #+#    #+#             */
/*   Updated: 2024/12/20 16:08:12 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// first element must be shell command and all elements after must be flags
char	**create_cmd_args(char *cmd)
{
	char **cmd_args;
	cmd_args = ft_split(cmd, ' ');
	if (cmd_args == NULL)
		handle_error("create cmd_args failed");
	return (cmd_args);
}

