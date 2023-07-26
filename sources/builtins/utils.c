// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   utils.c                                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/07/10 13:28:05 by wmoughar          #+#    #+#             */
// /*   Updated: 2023/07/26 18:28:59 by cmenke           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../includes/minishell.h"

// void	free_env(t_env *env)
// {
// 	while (env)
// 	{
// 		free(env->name);
// 		free(env->value);
// 		env = env->next;
// 	}
// 	free(env);
// }

// t_env	*ft_search(t_env *env, char *name)
// {
// 	t_env	*target;

// 	target = env;
// 	if (!target)
// 		return (NULL);
// 	while (target && ft_strcmp(target->name, name))
// 		target = target->next;
// 	return (target);
// }

// t_env	*update_value(t_env *env, char *name, char *new_val)
// {
// 	t_env	*tmp;

// 	tmp = ft_search(env, name);
// 	if(tmp)
// 	{
// 		free(tmp->value);
// 		tmp->value = ft_strdup(new_val);
// 	}
// 	return (tmp);
// }
