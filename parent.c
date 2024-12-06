/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:31:20 by phhofman          #+#    #+#             */
/*   Updated: 2024/12/06 09:41:34 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*run_cmd2(char *cmd_pathname, char *cmd_args[], char *filename);

void	parent(int pipe_fd[2], char *outfile, char *cmd, char *envp[])
{
	char	buffer[256];
	int		bytes_read;
	char	*res = "";

	bytes_read = 0;
	close(pipe_fd[1]);
	wait(NULL);
	dup2(pipe_fd[0],STDIN_FILENO);
	close(pipe_fd[0]);
	// while ((bytes_read = read(0, buffer, sizeof(buffer) - 1)) > 0)
	// {	
	// 	buffer[bytes_read] = '\0';
	// 	res = ft_strjoin(res, buffer);
	// }
	char **cmd_args;
	char *cmd_pathname;
	// printf("%s",res);
	cmd_args = create_cmd_args(cmd);
	cmd_pathname = get_cmd_pathname(cmd_args[0], envp);
	print_cmd(cmd_args);
	ft_printf("%s\n", cmd_pathname);
	run_cmd2(cmd_pathname, cmd_args, outfile);
	// print_cmd(cmd_args);
	// ft_printf("%s",final);
}

void	*run_cmd2(char *cmd_pathname, char *cmd_args[], char *filename)
{
	// int p_fd[2];
	// pid_t pid;
	// char	buffer[256];
	// int		bytes_read;
	// char	*res = "";

	// while ((bytes_read = read(0, buffer, sizeof(buffer) - 1)) > 0)
	// {	
	// 	buffer[bytes_read] = '\0';
	// 	res = ft_strjoin(res, buffer);
	// }
	
	int		fd;
	
	if (access(filename, W_OK) != 0)
	{
		perror("read acces failed");
		exit(EXIT_FAILURE);
	}
	fd = open(filename, O_WRONLY);
	if (fd < 0)
	{
		perror("infile open failed");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	execve(cmd_pathname, cmd_args, NULL);
	perror("execve run_cmd");
	
	exit(1);
}