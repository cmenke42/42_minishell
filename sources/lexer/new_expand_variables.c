// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   new_expand_variables.c                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/08/02 13:30:24 by cmenke            #+#    #+#             */
// /*   Updated: 2023/08/02 13:55:07 by cmenke           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../includes/minishell.h"

// bool	ft_execute_variable_expansion_case(char **string, char **token, bool in_double_quotes)
// {
// 	char	next_char;

// 	next_char = *(*string + 1);
// 	//keep the dollar sign
// 	// $ \0     $\t  \0 || '$' || "$''" "$""" || $\0
// 	if (ft_is_whitespace(next_char) || (in_double_quotes && ft_is_char_quote(next_char)) || !next_char)
// 	{
// 		(*string)++;
// 	}
// 	//keep the $$ -> getpid is forbidden
// 	else if(next_char == '$')
// 	{
// 		(*string) += 2;
// 	}
// 	//remove the dollar sign
// 	// $"abc"  $'abc'
// 	else if (!in_double_quotes && ft_is_char_quote(*(*string + 1)))
// 	{
// 		// ft_remove_dollar() ||ft_expand_to_nothing()
// 	}
// 	//exit code $?
// 	else if ((next_char) == '?')
// 	{
// 		// ft_expand_to_exit_code()
// 	}
// 	//replace with untrimmed value
// 	else if (in_double_quotes)
// 	{
// 		// ft_expand_to_untrimmed_value()	
// 	}
// 	//replace with trimmed value
// 	else
// 	{
// 		// ft_expand_to_trimmed_value()
// 	}
// 	return (true);
// }




























































// 		// ft_remove_dollar() ||ft_expand_to_nothing()
// 		// if (!ft_replace_variable_name_with_value(string, token, NULL, NULL))
// 		// 	return (false);




// // ft_expand_to_exit_code
// // 		if (g_signal_number != 0)
// // 		{
// // 			shell_data->exit_code = g_signal_number + 128;// check which value it should have
// // 			g_signal_number = 0;
// // 		}
// // 		exit_code = ft_itoa(shell_data->exit_code);
// // 		if (!exit_code)
// // 			return (false);
// // 		if (!ft_replace_variable_name_with_value(string, token, NULL, exit_code))
// // 			return (false);



// // ft_expand_to_untrimmed_value
// // 		if (!ft_get_variable_name(*string, &variable_name))
// // 			return (false);
// // 		if (!ft_replace_variable_name_with_value(string, token, variable_name, ft_get_variable_value(shell_data->env_list, variable_name)))
// // 			return (false);


// // ft_expand_to_trimmed_value()
// // 		if (!ft_get_variable_name(*string, &variable_name))
// // 			return (false);
// // 		value = ft_get_variable_value(shell_data->env_list, variable_name);
// // 		trimmed = ft_trim_variable_value(value);
// // 		if (!ft_replace_variable_name_with_value(string, token, variable_name, trimmed))
// // 			return (false);