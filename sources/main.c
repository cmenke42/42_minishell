/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 00:30:06 by cmenke            #+#    #+#             */
/*   Updated: 2023/07/23 17:11:00 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//take care that it frees all neccessary things
void	ft_exit_ctrl_d()
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	//rl_clear_history();
	exit(0);
}

//handles the ctrl-C key.
// rl_replace_line(PROMPT, 1); -> 1 clears the undo list
// of the current line (cmd z)
void ft_sig_sigint_handler(int sig_num)
{
	if (sig_num == SIGINT)
	{
		// rl_replace_line("", 1);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

int	main(int argc, char **argv, char **envp)
{
	char			*line_read;
	t_shell_data	*shell_data;

	//what to do when we get arguments for the minishell?
	shell_data = ft_calloc(1, sizeof(t_shell_data));
	if (!shell_data)
		perror("struct allocation error");
	//to ignore the SIG_QUIT signal from ctrl- Backslash
	signal(SIGQUIT, SIG_IGN);
	// handles the ctrl-C key.
	signal(SIGINT, ft_sig_sigint_handler);
	
	t_env *env = store_env(envp);
	shell_data->env_list = env;
	while (1)
	{
		line_read = readline(PROMPT);
		if (line_read && *line_read)
		{
			shell_data->command_line_read = line_read;
			if (!ft_process_command_line(shell_data))
			{
				continue ;
				//perform the clearing up
			}
			add_history(line_read);
			free(line_read);
			// rl_on_new_line();
		}
		else if (!line_read)
			ft_exit_ctrl_d();
	}
}
