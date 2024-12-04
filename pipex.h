/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:18:27 by phhofman          #+#    #+#             */
/*   Updated: 2024/12/04 16:04:36 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

#include <stdlib.h>
#include <stdio.h>
#include "./libft/libft.h"


// child
void	child(int pipe_fd[2], char *infile, char *cmd, char *envp[]);

// parent
void	parent(int pipe_fd[2], char *outfile, char *cmd);

// utils
char	**create_cmd_args(char *args, char *filename);
void	print_cmd(char **cmd);

// cmd
char	*get_cmd_pathname(char *cmd, char *envp[]);
void	run_cmd(char *cmd_pathname, char *cmd_args[]);

#endif