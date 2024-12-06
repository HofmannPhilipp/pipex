/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:18:27 by phhofman          #+#    #+#             */
/*   Updated: 2024/12/06 11:14:07 by phhofman         ###   ########.fr       */
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
void	child(int pipe_fd[2], char *infile, char *cmd, char *envp[]);

// parent
void	parent(int pipe_fd[2], char *outfile, char *cmd, char *envp[]);

// utils
char	**create_cmd_args(char *args);
void	print_cmd(char **cmd);
void	handle_error(char *error_msg);

// cmd
char	*get_cmd_pathname(char *cmd, char *envp[]);
char	*run_cmd(char *cmd_pathname, char *cmd_args[], char *filename);

#endif