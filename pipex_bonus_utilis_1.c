/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utilis_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:52:33 by ybouchma          #+#    #+#             */
/*   Updated: 2024/01/13 15:32:01 by ybouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

t_utilis	*init_t_utilis(int argc, char **argv, char **envp, int heredoc)
{
	t_utilis	*pipex;

	pipex = malloc(sizeof(t_utilis));
	if (!pipex)
		return (NULL);
	pipex->outfile = argv[argc - 1];
	if (!heredoc)
	{
		pipex->infile = argv[1];
		pipex->infile_fd = open(pipex->infile, O_RDONLY);
		pipex->heredoc = 0;
		pipex->outfile_fd = open(pipex->outfile, \
		O_CREAT | O_TRUNC | O_WRONLY, 0644);
	}
	else
	{
		pipex->infile = NULL;
		pipex->heredoc = 1;
		pipex->outfile_fd = open(pipex->outfile, O_CREAT | 01 | O_APPEND, 0644);
	}
	pipex->envp = envp;
	pipex->argc = argc;
	pipex->argv = argv;
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
