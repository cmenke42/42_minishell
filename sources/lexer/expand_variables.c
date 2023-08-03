/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 18:32:40 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/03 22:43:19 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_update_quote_state(bool *in_single_quotes,
				bool *in_double_quotes, char c);

bool	ft_expand_variables(t_list **tokens, t_shell_data *shell_data)
{
	t_list		*previous;
	t_list		*current;
	t_list		*next;

	previous = NULL;
	current = *tokens;
	while (current)
	{
		next = current->next;
		if (!ft_do_variable_expansion(&((t_tokens *)current->content)->token,
				shell_data, false))
			return (ft_putendl_fd("error - variable expansion", 2), false);
		if (!ft_strcmp(((t_tokens *)current->content)->token, ""))
			ft_cut_out_empty_node(tokens, previous, &current);
		else
			previous = current;
		current = next;
	}
	return (true);
}

bool	ft_do_variable_expansion(char **string, t_shell_data *shell_data,
				bool ignore_quotes)
{
	char	*moving_string;
	bool	in_double_quotes;
	bool	in_single_quotes;
	int		expansion_case;

	moving_string = *string;
	in_double_quotes = false;
	in_single_quotes = false;
	while (*moving_string)
	{
		if (!ignore_quotes)
			ft_update_quote_state(&in_single_quotes,
				&in_double_quotes, *moving_string);
		if (*moving_string == '$' && !in_single_quotes)
		{
			expansion_case = ft_get_expansion_case(&moving_string,
					in_double_quotes);
			if (!ft_handle_variable_expansion(expansion_case, &moving_string,
					string, shell_data))
				return (false);
		}
		if (*moving_string)
			moving_string += 1;
	}
	return (true);
}

static void	ft_update_quote_state(bool *in_single_quotes,
				bool *in_double_quotes, char c)
{
	if (c == '\'' && !*in_double_quotes)
		*in_single_quotes = !*in_single_quotes;
	else if (c == '\"' && !*in_single_quotes)
		*in_double_quotes = !*in_double_quotes;
}

bool	ft_handle_variable_expansion(int expansion_case, char **string,
			char **token, t_shell_data *shell_data)
{
	char	*name;
	char	*value;
	bool	error;

	name = NULL;
	value = NULL;
	error = false;
	if (expansion_case == v_exit_code || expansion_case == v_trim_value
		|| expansion_case == v_untrimmed_value)
	{
		if (!ft_get_variable_name(*string, &name))
			error = true;
		else if (!ft_get_variable_value(name, &value, shell_data->env_list))
			error = true;
		else if (expansion_case == v_trim_value && !ft_trim_value(&value))
			error = true;
		else if (expansion_case == v_exit_code
			&& !ft_get_exit_code_string(&name, &value, shell_data->exit_code))
			error = true;
		else if (!ft_replace_name_with_value(string, token, name, value))
			error = true;
	}
	ft_free_pointer_and_set_to_null((void **)&name);
	ft_free_pointer_and_set_to_null((void **)&value);
	return (!error);
}

bool	ft_is_char_quote(char c)
{
	return (c == '\'' || c == '\"');
}

//start at 1 && len -1 for the dollar removal
bool	ft_get_variable_name(char *string, char **variable_name)
{
	int		i;
	char	*limiters;

	limiters = " \t\n$?\"\'=";
	i = 1;
	while (string[i] && !ft_strchr(limiters, string[i]))
		i++;
	if (i == 1)
		return (true);
	*variable_name = ft_substr(string, 1, i - 1);
	if (!variable_name)
		return (perror("error creating variable_name"), false);
	return (true);
}

bool	ft_get_variable_value(char *name, char **value, t_list *env_list)
{
	t_list	*variable_node;

	if (!name)
		return (true);
	variable_node = ft_search_for_env_variable(name, env_list);
	if (variable_node)
	{
		if (((t_env *)variable_node->content)->value)
		{
			*value = ft_strdup(((t_env *)variable_node->content)->value);
			if (!*value)
				return (perror("error creating value"), false);
		}
	}
	return (true);
}

void	ft_cut_out_empty_node(t_list **tokens, t_list *previous_token_node,
			t_list **current_token_node)
{
	t_list	*temp;

	temp = *current_token_node;
	if (previous_token_node)
		previous_token_node->next = (*current_token_node)->next;
	*current_token_node = (*current_token_node)->next;
	if (temp == *tokens)
		*tokens = *current_token_node;
	ft_lstdelone(temp, ft_clear_token);
}

bool	ft_get_exit_code_string(char **name, char **value, int exit_code)
{
	*value = ft_itoa(exit_code);
	*name = ft_strdup("?");
	if (!*name || !*value)
		return (perror("error creating exit_code string"), false);
	return (true);
}
