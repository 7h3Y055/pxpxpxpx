/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utilis_0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:51:32 by ybouchma          #+#    #+#             */
/*   Updated: 2024/01/13 15:31:26 by ybouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_input_data(char *limiter)
{
	char	*str;
	char	*tmp;

	str = NULL;
	while (1)
	{
		ft_putstr_fd("heredoc> ", 1);
		tmp = get_next_line(0);
		if (!tmp)
			ft_putchar_fd('\n', 1);
		else
			tmp[ft_strlen(tmp) - 1] = 0;
		if (tmp && ft_strncmp(tmp, limiter, ft_strlen(limiter) + 1) == 0)
		{
			free(tmp);
			break ;
		}
		str = ft_merge(str, tmp);
	}
	get_next_line(INT_MAX);
	return (str);
}

char	*ft_merge(char *s1, char *s2)
{
	char	*tmp;

	if (!s1 && !s2)
		return (NULL);
	if (s1 && !s2)
		return (s1);
	else if (!s1 && s2)
		return (s2);
	else
	{
		tmp = ft_strjoin(s1, s2);
		free(s1);
		free(s2);
	}
	return (tmp);
}

char	*get_binary_path(char **envp, char *binary)
{
	int		i;
	char	*path;
	char	**paths;

	i = -1;
	if (access(binary, X_OK) == 0)
		return (binary);
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = &envp[i][5];
			break ;
		}
	}
	paths = ft_split(path, ':');
	path = access_path(paths, binary);
	if (path == NULL)
		ft_error(binary);
	i = 0;
	while (paths[i] != NULL)
		free(paths[i++]);
	free(paths);
	return (path);
}

char	*access_path(char **paths, char *binary)
{
	int		i;
	char	*tmp;
	char	*path;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin("/", binary);
		path = ft_strjoin(paths[i], tmp);
		free(tmp);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

void	*ft_error(char *str)
{
	char	*buffer;
	char	*tmp;

	buffer = ft_strjoin("command not found: ", str);
	tmp = ft_strjoin(buffer, "\n");
	write(2, tmp, ft_strlen(tmp));
	free(tmp);
	free(buffer);
	return (NULL);
}
