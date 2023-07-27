// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   new_cd.c                                           :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/07/27 18:17:24 by cmenke            #+#    #+#             */
// /*   Updated: 2023/07/27 18:44:17 by cmenke           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../includes/minishell.h"

// int	ft_cd(char **arguments, t_list **env_list)
// {
// 	t_list	*home_node;
// 	t_list	*pwd_node;

// 	home_node = ft_search_for_env_variable("HOME", *env_list);
// 	if (!arguments[1] && !home_node)
// 		ft_print_cd_error("cd", "HOME not set");
// 	else if (home_node)
// 	{
// 		if (ft_update_or_add_env_variable("OLDPWD", env_list, ((t_env *)home_node->content)->value) == __system_call_error)
// 			return (__system_call_error);
// 	}
// 	return (__success);
// }

// void	ft_print_cd_error(char *input, char *message)
// {
// 	ft_putstr_fd("minishell: ", 2);
// 	if (input)
// 		ft_putstr_fd(input, 2);
// 	ft_putstr_fd(": ", 2);
// 	ft_putendl_fd(message, 2);
// }