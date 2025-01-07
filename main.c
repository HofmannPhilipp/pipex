/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:02:11 by phhofman          #+#    #+#             */
/*   Updated: 2024/12/23 14:12:16 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


int	main(int argc, char *argv[], char *envp[])
{
	if (argc != 5)
	{
		ft_printf("Execute: %s <infile> <cmd1> <cmd2> <outfile>\n", argv[0]);
		handle_error("Error: Invalid arguments");
	}
	pipex(argv, envp);
	return (0);
}
