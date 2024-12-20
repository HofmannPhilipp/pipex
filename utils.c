/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:20:23 by phhofman          #+#    #+#             */
/*   Updated: 2024/12/20 16:15:56 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	handle_error(char *error_msg)
{
	perror(error_msg);
	exit(EXIT_FAILURE);
}

char	*get_envp(char *name, char *envp[])
{
	char	*sub;
	int		i;
	size_t	len;

	len = ft_strlen(name);
	i = 0;
	while (envp[i] != NULL)
	{
		sub = ft_substr(envp[i], 0, len);
		if (sub == NULL)
			handle_error("get_cmd_path malloc failed");
		if (ft_strncmp(name, sub, len) == 0)
		{
			free(sub);
			return (envp[i] + len + 1);
		}
		free(sub);
		i++;
	}
	handle_error("No PATHS found in envp");
	return (NULL);
}
char	*get_cmd_path(char *cmd, char *envp[])
{
	char	**paths;
	int		i;
	char	*path;

	paths = ft_split(get_envp("PATH", envp), ':');
	cmd = ft_strjoin("/", cmd);
	if (cmd == NULL || paths == NULL)
		handle_error("Malloc failed in get_cmd_path");
	i = 0;
	while (paths[i] != NULL)
	{
		path = ft_strjoin(paths[i], cmd);
		if (path == NULL)
			handle_error("get_cmd_path join malloc failed");
		if (access(path, F_OK | X_OK) == 0)
		{
			free(cmd);
			free_split(paths);
			return (path);
		}
		free(path);
		i++;
	}
	free(cmd);
	free_split(paths);
	handle_error("No path found");
	return (NULL);
}

