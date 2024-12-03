/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:18:27 by phhofman          #+#    #+#             */
/*   Updated: 2024/12/03 16:44:35 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

#include <stdlib.h>
#include <stdio.h>
#include "./libft/libft.h"


// child
void	child(int pipe_fd[2], char *infile, char *cmd);

// parent
void	parent(int pipe_fd[2], char *outfile, char *cmd);

// utils
char	**create_cmd(char *args);
void	print_cmd(char **cmd);

#endif