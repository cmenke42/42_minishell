/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_childs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 01:30:32 by cmenke            #+#    #+#             */
/*   Updated: 2023/06/07 16:53:48 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_close_all_pipes(int pipes[][2], int nbr_pipes)
{
	int	i;

	i = 0;
	while (i < nbr_pipes)
	{	
		if (pipes[i][0] > 2)
		{
			printf("closing pipe nbr: %d, FD:%d\n", i, pipes[i][0]);
			close(pipes[i][0]);
		}
		if (pipes[i][1] > 2)
		{
			printf("closing pipe nbr: %d, FD:%d\n", i, pipes[i][1]);
			close(pipes[i][1]);
		}
		i++;
	}
	//free the array after closing all the pipes
	// i = 0;
	// while (i < nbr_pipes)
	// 	free(pipes[i++]);
	// free(pipes);
}


void	ft_child_process_executor(t_data *data, t_child_cmd *command ,int i)
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
			ft_child_process_executor(data, data->command, i);
		}
		i++;
	}
	//wait for all children to finish
	waitpid(pids[--i], &stat_loc, 0);
	printf("waiting for pid %d\n", pids[i]);
	if (WIFEXITED(stat_loc))
		exit_code = WEXITSTATUS(stat_loc);
	while (--i >= 0)
	{
		printf("waiting for pid %d\n", pids[i]);
		waitpid(pids[i], NULL, 0);
	}
	i = 0;
	//print pids
	while (i < nbr_cmds)
	{
		printf("pid %d: %d\n", i, pids[i]);
		i++;
	}
	//close all pipes
	ft_close_all_pipes(pipes, nbr_cmds - 1);
	return (exit_code);
}