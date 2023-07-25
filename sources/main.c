/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 00:30:06 by cmenke            #+#    #+#             */
/*   Updated: 2023/07/25 13:43:09 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_signal_number;

//take care that it frees all neccessary things
void	ft_exit_ctrl_d()
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	rl_clear_history();
	exit(0);
}

//handles the ctrl-C key.
// rl_replace_line(PROMPT, 1); -> 1 clears the undo list
// of the current line (cmd z)
void ft_sig_sigint_handler(int sig_num)
{
	g_signal_number = sig_num;
	rl_replace_line("", 1);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_set_minisell_signals(void)
{
	//to ignore the SIG_QUIT signal from ctrl- Backslash
	signal(SIGQUIT, SIG_IGN);
	// handles the ctrl-C key.
	signal(SIGINT, ft_sig_sigint_handler);
}

void	ft_restore_default_signals(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_shell_data	*shell_data;
	int				exit_code;
	int				status;

	exit_code = 0;
	g_signal_number = 0;
	//what to do when we get arguments for the minishell? -> nothing
	shell_data = ft_calloc(1, sizeof(t_shell_data));
	if (!shell_data)
		return (perror("shell_data struct allocation error"), 1);
	ft_set_minisell_signals(); //what should happen in minishell when we get a signal?
	//free something?
	//what should happen when we get a signal during child process?
	t_env *env = store_env(envp);
	shell_data->env_list = env;
	increase_shlvl(shell_data);
	while (1)
	{
		shell_data->command_line_read = readline(PROMPT);
		if (shell_data->command_line_read && *shell_data->command_line_read)
		{
			status = ft_process_command_line(shell_data);
			if (status != __system_call_error && status != __dont_add_to_history)
			{
				add_history(shell_data->command_line_read);
				// continue ;
				//perform the clearing up
			}
			else if (status == __system_call_error)
				exit_code = 1; //exit the shell
			// rl_on_new_line();
		}
		else if (!shell_data->command_line_read)
			ft_exit_ctrl_d();
		ft_free_shell_data_for_next_command(shell_data);
	}
	exit (exit_code);
}

int	ft_process_command_line(t_shell_data *shell_data)
{
	int	status;

	status = ft_check_equal_quote_amt(shell_data->command_line_read);
	if (!status)
		status = ft_create_tokens_for_sequence(shell_data->command_line_read, &shell_data->all_tokens);
	if (status == __success && (!shell_data->all_tokens))
		return (__dont_add_to_history);
	// else if (ft_is_syntax_error(shell_data))
	// 	return (false);
	// ft_split_tokens_in_sequences(shell_data);
	// ft_search_for_variable_expansion(shell_data);
	// // ft_lstclear(&shell_data->all_tokens, ft_clear_token);
	// ft_execute_commands(shell_data);
	// //syntax error for ambibous redirect????
	// // //freeing the list of command sequences
	// // ft_lstclear(&shell_data->command_sequences, ft_clear_command_sequence);
	return (status);
}