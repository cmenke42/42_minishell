/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:48:03 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/03 21:41:12 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//what to do when we get arguments for the minishell? -> nothing
int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_shell_data	*shell_data;
	int				exit_code;
	int				status;

	exit_code = 0;
	g_signal_number = 0;
	shell_data = ft_calloc(1, sizeof(t_shell_data));
	if (!shell_data)
		return (perror("shell_data struct allocation error"), 1);
	if (ft_store_env_in_list(envp, &shell_data->env_list) == __system_call_error)
		return (printf("error storing env in list\n"), ft_free_shell_data(shell_data, true), exit(1), 1);
	if (ft_prepare_env_variables(shell_data) == __system_call_error)
		return (ft_free_shell_data(shell_data, true), exit(1), 1);
	ft_set_minisell_signals();
	while (1)
	{
		shell_data->command_line_read = readline(PROMPT);
		if (shell_data->command_line_read && *shell_data->command_line_read)
		{
			// printf("command line read: %s\n", shell_data->command_line_read);
			// ft_replace_variable_name_with_value(&shell_data->command_line_read, &shell_data->command_line_read, NULL, "Alabama");
			// printf("command line read: %s\n", shell_data->command_line_read);
			// continue;
			status = ft_process_command_line(shell_data);
			if (status != __system_call_error && status != __dont_add_to_history)
				add_history(shell_data->command_line_read);
			else if (status == __system_call_error)
				return (ft_free_shell_data(shell_data, true), exit(1), 1);
			// rl_on_new_line();
		}
		else if (!shell_data->command_line_read)
			ft_exit_ctrl_d(shell_data);
		ft_delete_heredoc_files(shell_data->heredocs);
		ft_free_shell_data(shell_data, false);
	}
	exit (exit_code);
}

int	ft_process_command_line(t_shell_data *shell_data)
{
	int	status;

	if (!ft_is_equal_quote_ammount(shell_data->command_line_read))
		return (__syntax_error);
	status = ft_tokenize_command_line(shell_data->command_line_read, &shell_data->all_tokens);
	if (status)
		return (status);
	if (!shell_data->all_tokens)
		return (__dont_add_to_history);
	ft_lstiter(shell_data->all_tokens, ft_assign_token_type);
	if (ft_is_syntax_error_in_tokens(shell_data->all_tokens))
		return (__syntax_error);
	status = ft_handle_heredocs(shell_data);
	if (status)
		return (status);
	if (!ft_expand_variables(&shell_data->all_tokens, shell_data))
		return (__system_call_error);
	status = ft_split_tokens_in_sequences(shell_data->all_tokens, &shell_data->command_sequences);
	if (status)
		return (status);
	status = ft_execute_commands(shell_data);  //handle the syntax errors of builtin commands??? // is there a case where a syntax error comes back?? -> when open failed
	// //syntax error for ambibous redirect????
	return (status);
}

int	ft_prepare_env_variables(t_shell_data *shell_data)
{
	char *pwd_name;
	char *pwd_value;

	pwd_value = NULL;
	if (increase_shlvl(&shell_data->env_list) == __system_call_error)
		return (__system_call_error);
	if (ft_update_or_add_env_variable("OLDPWD", &shell_data->env_list, NULL, NULL) == __system_call_error)
		return (__system_call_error);
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
		if (store_var_in_node(env_list, name, value, "=") == __system_call_error)
			return (free(name), free(value), __system_call_error);
		return (__success);
	}
	value = ft_itoa(ft_atoi(((t_env*)shlvl->content)->value) + 1);
	if (!value)
		return (free(name), perror("error creating itoa value in increase_shlvl"), __system_call_error);
	ft_assign((t_env *)shlvl->content, name, value, "=");
	return (__success);
}



void	ft_exit_ctrl_d(t_shell_data *shell_data)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	rl_clear_history();
	ft_free_shell_data(shell_data, true);
	exit(0);
}
