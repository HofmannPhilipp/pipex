/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:20:23 by phhofman          #+#    #+#             */
/*   Updated: 2024/12/06 11:03:26 by phhofman         ###   ########.fr       */
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



char	*run_cmd(char *cmd_pathname, char *cmd_args[], char *filename)
{
	int p_fd[2];
	pid_t pid;
	char	buffer[256];
	int		bytes_read;
	char	*res = "";
	int		fd_infile;
	
	if (access(filename, R_OK) != 0)
		handle_error("Read access failed: ");
	fd_infile = open(filename, O_RDONLY);
	if (fd_infile < 0)
		handle_error("Infile open failed: ");
	if (pipe(p_fd) == -1)
		handle_error("Pipe failed: ");
	// pid = fork();
	// if (pid < 0)
	// 	handle_error("Fork failed: ");
	if (pid == 0)
	{
		close(p_fd[0]);
		dup2(p_fd[1], STDOUT_FILENO);
		close(p_fd[1]);
		dup2(fd_infile, STDIN_FILENO);
		close(fd_infile);
		execve(cmd_pathname, cmd_args, NULL);
		handle_error("Execve failed: ");
	}
	else
	{
		bytes_read = 0;
		close(p_fd[1]);
		wait(NULL);
		while ((bytes_read = read(p_fd[0], buffer, sizeof(buffer) - 1)) > 0)
		{	
			buffer[bytes_read] = '\0';
			res = ft_strjoin(res, buffer);
		}
		close(p_fd[0]);
	}
	return (res);
}