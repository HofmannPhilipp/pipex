/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:10:15 by phhofman          #+#    #+#             */
/*   Updated: 2025/01/29 13:32:14 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// first element must be shell command and all elements after must be flags
char	**create_cmd_args(char *cmd)
{
	char	**cmd_args;

	cmd_args = ft_split(cmd, ' ');
	return (cmd_args);
}
