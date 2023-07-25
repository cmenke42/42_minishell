/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmoughar <wmoughar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 14:08:54 by wmoughar          #+#    #+#             */
/*   Updated: 2023/07/25 11:59:21 by wmoughar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"

t_env	*ft_create_node(char *name, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (new)
	{
		new->name = ft_strdup(name);
		new->value = ft_strdup(value);
		new->next = NULL;
	}
	return (new);
}

int	ft_check_name(char *name)
{
	if ((ft_isalpha(name[0]) == 0 && name[0] != '_')) 
	{
		printf("minishell: export: `%c': not a valid identifier\n", name[0]);
		return (0);
	}
	int i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]))
		{
			printf("minishell: export: `%s': not a valid identifier\n", name);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_check_name_start(char *s)
{
	if (s[0] == '=')
	{
		printf("minishell: export: `%c': not a valid identifier\n",s[0]);
		return(0);
	}
	return (1);
}

int	ft_check_duplicate(t_env *env, char *name, char *new_name)
{
	while (env)
	{
		if (ft_strncmp(name, new_name, ft_strlen(name)) == 0)
			return 1;
		env = env->next;
	}
	return 0;
}

t_env	*find_and_replace(t_env *env, t_env *new)
{
	while (env)
	{
		if (ft_strncmp(env->name, new->name, ft_strlen(env->name)) == 0)
			env->value = new->value;
		env = env->next;
	}
	return env;
}


// char *reverse_split(char *name, const char *value)
// {
//     int i = 0;
//     int j = 0;

//     while (name[i])
//         i++;
// 	name[i] = '=';
// 	i++;
//     while (value[j])
//     {
//         name[i] = value[j];
//         i++;
//         j++;
//     }
//     name[i] = '\0';
//     return name;
// }

char *reverse_split(const char *name, const char *value)
{
    int i = 0;
    int j = 0;
    size_t name_len = ft_strlen(name);
    size_t value_len = ft_strlen(value);

    char *result = malloc(name_len + value_len + 2);  // +2 for '=' and '\0'
    if (result == NULL) {
        // Handle memory allocation failure
        return NULL;
    }

    ft_strlcpy(result, name, ft_strlen(name) + 1);
    result[name_len] = '=';
    i = name_len + 1;

    while (value[j]) {
        result[i] = value[j];
        i++;
        j++;
    }
    result[i] = '\0';

    return result;
}