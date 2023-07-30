/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:48:03 by cmenke            #+#    #+#             */
/*   Updated: 2023/07/30 21:28:20 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_signal_number;

//take care that it frees all neccessary things
void	ft_exit_ctrl_d(t_shell_data *shell_data)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	rl_clear_history();
	ft_free_shell_data(shell_data, true);
	exit(0);
}

// void ft_sig_sigint_handler_heredoc_reading(int sig_num)
// {
// 	g_signal_number = sig_num;
// 	rl_replace_line("", 1);
// 	write(1, "\n", 1);
// 	rl_on_new_line();
// 	close(0);
// 	// rl_redisplay(); //cat|ls case -> how to handle Minishell:$ Minishell:
// }

//handles the ctrl-C key during execution of a command in the parent process
// rl_replace_line(PROMPT, 1); -> 1 clears the undo list
// of the current line (cmd z)
void ft_sig_sigint_handler_parent_execution(int sig_num)
{
	g_signal_number = sig_num;
	rl_replace_line("", 1);
	write(1, "\n", 1);
	rl_on_new_line();
	// rl_redisplay(); //cat|ls case -> how to handle Minishell:$ Minishell:
}

void ft_sig_sigquit_handler_parent_execution(int sig_num)
{
	g_signal_number = sig_num;
	rl_replace_line("", 1);
	write(1, "\n", 1);
	rl_on_new_line();
	// rl_redisplay(); //cat|ls case -> how to handle Minishell:$ Minishell:
}

void ft_sig_sigint_handler_prompt(int sig_num)
{
	g_signal_number = sig_num;
	rl_replace_line("", 1);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay(); //cat|ls case -> how to handle Minishell:$ Minishell:
}

void	ft_set_minisell_signals(void)
{
	//to ignore the SIG_QUIT signal from ctrl- Backslash
	signal(SIGQUIT, SIG_IGN);
	// handles the ctrl-C key.
	signal(SIGINT, ft_sig_sigint_handler_prompt);
}

void	ft_set_singals_handler_while_parent_execution(void)
{
	//to ignore the SIG_QUIT signal from ctrl- Backslash
	signal(SIGQUIT, ft_sig_sigquit_handler_parent_execution);
	// handles the ctrl-C key.
	signal(SIGINT, ft_sig_sigint_handler_parent_execution);
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
	if (ft_store_env_in_list(envp, &shell_data->env_list) == __system_call_error)
		return (printf("error storing env in list\n"), ft_free_shell_data(shell_data, true), exit(1), 1);
	if (ft_prepare_env_variables(shell_data) == __system_call_error)
		return (ft_free_shell_data(shell_data, true), exit(1), 1);
	ft_set_minisell_signals(); //what should happen in minishell when we get a signal?
	//free something?
	//what should happen when we get a signal during child process?
	// // increase_shlvl(shell_data);
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
			ft_exit_ctrl_d(shell_data);
		ft_free_shell_data(shell_data, false);
	}
	exit (exit_code);
}

int	ft_process_command_line(t_shell_data *shell_data)
{
	int	status;

	status = ft_check_equal_quote_amt(shell_data->command_line_read);
	if (status == __success)
		status = ft_create_tokens_for_sequence(shell_data->command_line_read, &shell_data->all_tokens);
	else
		return (status);
	if (!shell_data->all_tokens)
		return (__dont_add_to_history);
	if (ft_is_syntax_error(shell_data))
		return (__syntax_error);
	status = ft_handle_heredocs(shell_data);
	if (status)
		return (status);
	if (!ft_split_tokens_in_sequences(shell_data))
		return (__system_call_error);
	if (!ft_search_for_variable_expansion(shell_data)) //remove tokens that got empty after expansion
		return (__system_call_error);
	// // ft_lstclear(&shell_data->all_tokens, ft_clear_token);
	if (!ft_execute_commands(shell_data))  //handle the syntax errors of builtin commands??? // is there a case where a syntax error comes back?? -> when open failed
		return (__system_call_error);
	// //syntax error for ambibous redirect????
	// // //freeing the list of command sequences
	// // ft_lstclear(&shell_data->command_sequences, ft_clear_command_sequence);
	return (status);
}

int	ft_prepare_env_variables(t_shell_data *shell_data)
{
	char *pwd_name;
	char *pwd_value;

	pwd_value = NULL;
	if (increase_shlvl(&shell_data->env_list) == __system_call_error)
		return (__system_call_error);
	if (!ft_search_for_env_variable("OLDPWD", shell_data->env_list))
	{
		if (ft_update_or_add_env_variable("OLDPWD", &shell_data->env_list, NULL, NULL) == __system_call_error)
			return (__system_call_error);
	}
	if (!ft_search_for_env_variable("PWD", shell_data->env_list))
	{
		pwd_name = ft_strdup("PWD");
		if (!pwd_name)
			return (perror("error creating name in ft_prepare_env_variables"), __system_call_error);
		ft_pwd(&pwd_value, false);
		if (ft_update_or_add_env_variable(NULL, &shell_data->env_list, pwd_name, pwd_value) == __system_call_error)
			return (__system_call_error);
	}
	return (__success);
}

int	increase_shlvl(t_list **env_list)
{
	t_list	*shlvl;
	char	*name;
	char	*value;

	name = ft_strdup("SHLVL");
	if (!name)
		return (perror("error creating name in increase_shlvl"), __system_call_error);
	shlvl = ft_search_for_env_variable("SHLVL", *env_list);
	if (!shlvl || !((t_env*)shlvl->content)->value)
	{
		value = ft_strdup("1");
		if (!value)
			return (free(name), perror("error creating strudp value in increase_shlvl"), __system_call_error);
		if (ft_store_one_variable_in_node(env_list, name, value, "=") == __system_call_error)
			return (free(name), free(value), __system_call_error);
		return (__success);
	}
	value = ft_itoa(ft_atoi(((t_env*)shlvl->content)->value) + 1);
	if (!value)
		return (free(name), perror("error creating itoa value in increase_shlvl"), __system_call_error);
	ft_assign_name_and_value_to_env_variable((t_env *)shlvl->content, name, value, "=");
	return (__success);
}
