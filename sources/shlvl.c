// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   shlvl.c                                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: wmoughar <wmoughar@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/07/23 18:12:36 by wmoughar          #+#    #+#             */
// /*   Updated: 2023/07/23 18:29:40 by wmoughar         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../includes/minishell.h"

// t_env *increase_shlvl(t_shell_data *shell_data)
// {
// 	t_env	*shlvl;
// 	int		shlvl_atoi;
// 	char	*shlvl_itoa;

// 	shlvl = ft_search(shell_data->env_list, "SHLVL");
// 	if (!shlvl)
// 		return (NULL);
// 	shlvl_atoi = ft_atoi(shlvl->value) + 1;
// 	shlvl_itoa = ft_itoa(shlvl_atoi);
// 	free(shlvl->value);
// 	shlvl->value = shlvl_itoa;
// 	return (shlvl);
// }