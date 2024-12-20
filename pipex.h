/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:18:27 by phhofman          #+#    #+#             */
/*   Updated: 2024/12/20 16:06:23 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "./libft/libft.h"


// child
void	child(int end[2],char *argv[], char *envp[]);
// parent
void	parent(int end[2], char *argv[], char *envp[]);
// utils
void	free_split(char **split);
char	**create_cmd_args(char *args);
void	handle_error(char *error_msg);
char	*get_envp(char *name, char *envp[]);
char	*get_cmd_path(char *cmd, char *envp[]);


void	pipex(char *args[], char *envp[]);

#endif