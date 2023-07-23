/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 00:30:06 by cmenke            #+#    #+#             */
/*   Updated: 2023/07/23 18:35:50 by cmenke           ###   ########.fr       */
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
	(void)argc;
	(void)argv;
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
			// rl_on_new_line();
		}
		else if (!line_read)
			ft_exit_ctrl_d();
		ft_free_shell_data_for_next_command(shell_data);
	}
}

bool	ft_process_command_line(t_shell_data *shell_data)
{
	if (!ft_check_equal_quote_amt(shell_data->command_line_read))
		return (false);
	if (!ft_create_tokens_for_sequence(shell_data->command_line_read, &shell_data->all_tokens))
		return (false);
	if (ft_is_syntax_error(shell_data))
		return (false);
	ft_split_tokens_in_sequences(shell_data);
	ft_search_for_variable_expansion(shell_data);
	// ft_lstclear(&shell_data->all_tokens, ft_clear_token);
	ft_execute_commands(shell_data);
	//syntax error for ambibous redirect????
	// //freeing the list of command sequences
	// ft_lstclear(&shell_data->command_sequences, ft_clear_command_sequence);
	shell_data->all_tokens = NULL;
	shell_data->command_sequences = NULL;
	return (true);
}