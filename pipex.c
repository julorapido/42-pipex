/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:09:55 by jsaintho          #+#    #+#             */
/*   Updated: 2024/07/19 13:00:37 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// #1 Initiate Pipe						||	Pipe openned for parent && 
// #2 Create fork (child process)		||	fork wait for child process 
// #3 Child run [execve] and to pipe	||	
// #4 Pending parent take back control	||	parent is back [<=<=]
// ---------------------------     --------------------------------
// #++ Since we let child process write, we close its Read-End (pfd[0]). 
// #++ And since parent process reads, we close the Write-End (pfd[1]).
// ---------------------------     ------------------------------------
// #5 Use STDOUT && STDIN for pipe 		||  instead of random file ds

void	ft_execve(char *f_name, char *cmd, char **env, int is_parent)
{
	char	**ft_cmd;
	char	*path;
	int		fd;

	fd = open_file(f_name, is_parent);
	dup2(fd, is_parent);
	ft_cmd = ft_split(cmd, ' ');
	path = get_path(ft_cmd[0], env);
	if (execve(path, ft_cmd, env) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(ft_cmd[0], 2);
		ft_free_tab(ft_cmd);
		exit(0);
	}
}

int	main(int argc, char **argv, char **env)
{
	int		pfd[2];
	pid_t	pid;

	if (argc != 5)
		exit_handler(1);
	if (pipe(pfd) == -1)
		exit(-1);
	pid = fork();
	if (pid == -1)
		exit(-1);
	if (!pid)
	{
		dup2(pfd[1], 1);
		close(pfd[0]);
		ft_execve(argv[1], argv[2], env, 0);
	}
	else
	{
		dup2(pfd[0], 0);
		close(pfd[1]);
		ft_execve(argv[4], argv[3], env, 1);
	}
}
