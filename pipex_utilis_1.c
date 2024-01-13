/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utilis_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:51:37 by ybouchma          #+#    #+#             */
/*   Updated: 2024/01/13 15:33:29 by ybouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*free_split(char **param)
{
	int	i;

	i = 0;
	if (!param)
		return (NULL);
	while (param[i])
		free(param[i++]);
	free(param);
	return (NULL);
}

t_utilis	*init_t_utilis(int argc, char **argv, char **envp)
{
	t_utilis	*pipex;

	pipex = malloc(sizeof(t_utilis));
	if (!pipex)
		return (NULL);
	pipex->infile = argv[1];
	pipex->infile_fd = open(pipex->infile, O_RDONLY);
	pipex->envp = envp;
	pipex->argc = argc;
	pipex->argv = argv;
	pipex->outfile = argv[argc - 1];
	pipex->outfile_fd = open(pipex->outfile, O_CREAT \
			| O_TRUNC | O_WRONLY, 0644);
	return (pipex);
}

void	free_all(void *ptr1, void *ptr2, void *ptr3, void *ptr4)
{
	free(ptr1);
	free(ptr2);
	free(ptr3);
	free(ptr4);
	exit(1);
}

void	path_error(void)
{
	ft_putendl_fd("", 2);
	exit (1);
}
