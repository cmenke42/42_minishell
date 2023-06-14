/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_childs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 01:30:32 by cmenke            #+#    #+#             */
/*   Updated: 2023/06/14 23:26:30 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_error_ret_exit_code(char *error_text, int exit_code)
{
	if (exit_code == 127)
		ft_putendl_fd(error_text, 2);
	else
		perror(error_text);
	return (exit_code);
}

void	ft_close_standard_fd(void)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

void ft_close_all_pipes(int **pipes, int nbr_pipes)
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

bool	ft_check_if_builtin(t_data *data, t_child_cmd *command)
{
	int		cmd_length;

	cmd_length = 0;
	cmd_length = ft_strlen(command->cmd_args[0]);
	//how to manage the calling of the builtin and the correct closing of the pipes, redirection and freeing?
	if (cmd_length < 2 || cmd_length > 6)
		return (false);
	if (ft_strncmp("echo", command->cmd_args[0], cmd_length) == 0)
		return (true);
	else if (ft_strncmp("cd", command->cmd_args[0], cmd_length) == 0)
		return (true);
	else if (ft_strncmp("pwd", command->cmd_args[0], cmd_length) == 0)
		return (true);
	else if (ft_strncmp("export", command->cmd_args[0], cmd_length) == 0)
		return (true);
	else if (ft_strncmp("unset", command->cmd_args[0], cmd_length) == 0)
		return (true);
	else if (ft_strncmp("env", command->cmd_args[0], cmd_length) == 0)
		return (true);
	else if (ft_strncmp("exit", command->cmd_args[0], cmd_length) == 0)
		return (true);
	return (false);
}

bool	ft_check_if_cmd_path_is_valid(t_data *data, t_child_cmd *command)
{
	//do we need to chek if cmd_args is NULL?
	//check if the command is a builtin
	if (ft_check_if_builtin(data, command) == true)
	{
		printf("builtin found: %s\n", command->cmd_args[0]);
		return (true);
	}
	//check if the command is a relative path or an absolute path
	if (access(command->cmd_args[0], X_OK) == 0)
	{
		printf("relative path or absolute path found: %s\n", command->cmd_args[0]);
		return (true);
	}
	//check if the command is in the PATH from envp
	command->envp_paths = ft_get_envp_paths(data->envp);
	command->cmd_path = ft_get_cmd_path(command->envp_paths, command->cmd_args[0]);
	if (command->cmd_path != NULL)
	{
		printf("command found in PATH: %s\n", command->cmd_path);
		return (true);
	}
	//check if the command path is valid
	//if not, print error message and return false
	//if valid, return true
	return (false);
}


void	ft_child_process_executor(t_data *data, t_child_cmd *command ,int i)
{
	int		exit_code;

	exit_code = 0;
	//check if the command is a builtin
	//check if the command path is valid
	if (ft_check_if_cmd_path_is_valid(data, command) == false)
	{
		//print the error message
		printf("minishell: %s: command not found\n", command->cmd_args[0]);
		exit(127);
	}
	if (exit_code == 0 && command->input_fd != -1 &&
		(dup2(command->input_fd, STDIN_FILENO) == -1))
			exit_code = ft_error_ret_exit_code("dup2 error", 1);
	// else
	//check if a pipe input redirection is needed
	if (exit_code == 0 && command->output_fd != -1 &&
		(dup2(command->output_fd, STDOUT_FILENO) == -1))
			exit_code = ft_error_ret_exit_code("dup2 error", 1);
	// else
	//check if a pipe output redirection is needed
	ft_close_all_pipes(data->pipes, data->nbr_cmds - 1);
	if (exit_code == 0 && execve(command->cmd_path, command->cmd_args, data->envp) == -1)
		exit_code = ft_error_ret_exit_code("execve error", 1);
	ft_close_standard_fd();
	//call the clear function
	exit(exit_code);
	//When do we need to print the error message?
	//mange input redirection - 1. here_doc 2. < - stops at error
	// if ()
	//manage output redirection - left to right last one wins - stops at error
	//manage pipes
	//what happens to the content in the pipe when a command doesnt read it?
	//execute the command
	//clean up in case of error
	

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
			data->pipes = (int **)pipes;
			data->nbr_cmds = nbr_cmds;
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
	ft_close_all_pipes(data->pipes, data->nbr_cmds - 1);
	return (exit_code);
}