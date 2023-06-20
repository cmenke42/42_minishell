/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmoughar <wmoughar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:55:14 by wmoughar          #+#    #+#             */
/*   Updated: 2023/06/20 19:07:29 by wmoughar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int		ft_env_len(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

char	**sort_env(char **env, int env_len)
{
	int		sorted;
	int		i;
	char	*tmp;

	sorted = 0;
	while (env && sorted == 0)
	{
		sorted = 1;
		i = 0;
		while (i < env_len - 1)
		{
			if (strcmp(env[i], env[i + 1]) > 0)
			{
				tmp = env[i];
				env[i] = env[i + 1];
				env[i + 1] = tmp;
				sorted = 0;
			}
			i++;
		}
		env_len--;
	}
	return (env);
}

void	export(char **envp)
{
	int	i;
	
	i = 0;
	sort_env(envp, ft_env_len(envp));
			while (envp[i])
		{
			printf("declare -x ");
			printf("%s\n", envp[i]);
			i++;
		}
}

