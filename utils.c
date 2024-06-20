/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:33:17 by jsaintho          #+#    #+#             */
/*   Updated: 2024/06/20 15:20:25 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_handler(int n_exit)
{
	if (n_exit == -1)
		ft_putstr_fd("./pipex infile cmd cmd outfile\n", 2);
	exit(0);
}

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	open_file(char *file, int in_out)
{
	int	ret;

	if (in_out == 0)
		ret = open(file, O_RDONLY, 0777);
	if (in_out == 1)
		ret = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (ret == -1)
		exit(0);
	return (ret);
}

char	*get_env(char **env)
{
	int			i;
	int			j;
	char		*s;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		s = ft_substr(env[i], 0, j);
		if (ft_strcmp(s, &("PATH"[0])) == 0)
		{
			free(s);
			return (env[i] + j + 1);
		}
		free(s);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	char	**b_path;
	char	**e_cmd;
	char	*exec_cmd;
	char	*str_path;
	int		i;

	i = -1;
	b_path = ft_split(get_env(env), ':');
	e_cmd = ft_split(cmd, ' ');
	while (b_path[++i])
	{
		str_path = ft_strjoin(b_path[i], "/");
		exec_cmd = ft_strjoin(str_path, e_cmd[0]);
		free(str_path);
		if (access(exec_cmd, F_OK | X_OK) == 0)
		{
			ft_free_tab(e_cmd);
			return (exec_cmd);
		}
		free(exec_cmd);
	}
	ft_free_tab(e_cmd);
	ft_free_tab(b_path);
	return (cmd);
}
