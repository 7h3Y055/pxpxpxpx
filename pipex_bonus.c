/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:51:09 by ybouchma          #+#    #+#             */
/*   Updated: 2024/01/13 15:30:55 by ybouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_utilis	*pipex;

	if (argc < 5)
	{
		ft_putendl_fd("[+] Usage:", 1);
		ft_putendl_fd("./pipex_bonus <INFILE> <CMD> ... <CMD> <OUTFILE>", 1);
		ft_putendl_fd(\
			"./pipex_bonus here_doc <LIMITER> <CMD> ... <CMD> <OUTFILE>", 1);
		return (0);
	}
	if (ft_strncmp(argv[1], "here_doc", 10) == 0 && argc == 6)
		pipex = init_t_utilis(argc, argv, envp, 1);
	else
		pipex = init_t_utilis(argc, argv, envp, 0);
	if (pipex->infile_fd == -1)
	{
		perror(pipex->infile);
		free_all(pipex, NULL, NULL, NULL);
	}
	if (ft_strncmp(argv[1], "here_doc", 10) == 0)
		here_doc(pipex);
	else
		multi_pipes(pipex);
	free(pipex);
	return (0);
}

int	here_doc(t_utilis *pipex)
{
	char	*limiter;
	char	*input;
	int		fd[2];

	limiter = pipex->argv[2];
	input = get_input_data(limiter);
	if (pipe(fd) == -1)
		free_all(pipex, input, NULL, NULL);
	write(fd[1], input, ft_strlen(input));
	free(input);
	close(fd[1]);
	pipex->infile_fd = fd[0];
	multi_pipes(pipex);
	return (0);
}

int	multi_pipes(t_utilis *pipex)
{
	int	i;
	int	in;
	int	fd[2];

	i = 2;
	if (pipex->heredoc)
		i++;
	if (pipe(fd) == -1)
		free_all(pipex, NULL, NULL, NULL);
	child(pipex, pipex->argv[i++], pipex->infile_fd, fd);
	while (i < pipex->argc - 2)
	{
		in = fd[0];
		if (pipe(fd) == -1)
			free_all(pipex, NULL, NULL, NULL);
		child(pipex, pipex->argv[i], in, fd);
		i++;
	}
	fd[1] = pipex->outfile_fd;
	child(pipex, pipex->argv[i++], fd[0], fd);
	while (wait(NULL) != -1)
	{
	}
	return (0);
}

void	child(t_utilis *pipex, char *cmd, int in, int *fd)
{
	int		pid;
	char	**param;

	param = ft_split(cmd, ' ');
	pid = fork();
	if (pid == -1)
		free_all(pipex, free_split(param), NULL, NULL);
	else if (pid == 0)
		child_helper(pipex, fd, param, in);
	else
	{
		close(in);
		close(fd[1]);
	}
	free_split(param);
}

void	child_helper(t_utilis *pipex, int *fd, char **param, int in)
{
	char	*binary;

	binary = get_binary_path(pipex->envp, param[0]);
	if (!binary)
		free_all(pipex, free_split(param), ft_error(param[0]), NULL);
	if (dup2(fd[1], 1) == -1)
		free_all(pipex, binary, free_split(param), NULL);
	close(fd[1]);
	if (dup2(in, 0) == -1)
		free_all(pipex, binary, free_split(param), NULL);
	close(in);
	close(fd[0]);
	if (execve(binary, param, pipex->envp) != -1)
		free_all(pipex, binary, free_split(param), NULL);
	free(binary);
	exit(0);
}
