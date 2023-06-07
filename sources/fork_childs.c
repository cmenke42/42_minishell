/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_childs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 01:30:32 by cmenke            #+#    #+#             */
/*   Updated: 2023/06/07 14:47:48 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void	ft_child_process_executor(t_data *data, int i)
{
	printf("child process %d\n", i);
	exit(0);
}

int	ft_fork_childs(t_data *data, int nbr_cmds)
{
	int	pipes[nbr_cmds - 1][2];
	int	pids[nbr_cmds];
	int	i;
	int	stat_loc;
	int exit_code;

	stat_loc = 0;
	exit_code = 0;
	//create pipes except for the last one
	i = 0;
	while (i < nbr_cmds - 1)
	{
		if (pipe(pipes[i]) == -1)
		{
			//clear old pipes, free data, and call the custom exit function.
			exit(1);
		}
		i++;
	}
	//print_pipes(pipes, nbr_cmds);
	i = 0;
	while (i < nbr_cmds - 1)
	{
		printf("pipe %d: %d, %d\n", i, pipes[i][0], pipes[i][1]);
		i++;
	}
	i = 0;
	while (i < nbr_cmds)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			//clear old pipes, free data, and call the custom exit function.
			exit(2);
		}
		if (pids[i] == 0)
		{
			//child process
			ft_child_process_executor(data, i);
		}
		i++;
	}
	waitpid(pids[nbr_cmds - 1], stat_loc, 0);
	if (WIFEXITED(stat_loc))
		exit_code = WEXITSTATUS(stat_loc);
	i = 0;
	//print pids
	while (i < nbr_cmds)
	{
		printf("pid %d: %d\n", i, pids[i]);
		i++;
	}
	return (exit_code);
}