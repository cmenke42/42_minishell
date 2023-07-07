/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmoughar <wmoughar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 11:38:04 by wmoughar          #+#    #+#             */
/*   Updated: 2023/07/07 13:01:54 by wmoughar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
#include "../libft/libft.h"
#include <stdio.h>

typedef struct	s_env
{
	char	*name;
	char	*value;
	struct s_env	*next;
}	t_env;

int 	main(int argc, char **argv, char **env);
t_env	*ft_create_node(char *name, char *value);
void	export(t_env *envp);
void	print_env(t_env *envp);
void	free_split(char **arr);
t_env	*store_env(char **env);
t_env	*sort_env(t_env *env);
t_env	*add_var(t_env *envp, char *env);
void	ft_name_error(char c);
void	ft_check_name(t_env *env);
t_env	*add_to_list(t_env *head, char *var);
void	ft_check_name_start(char *s);
t_env *remove_from_list(t_env* head, char* name);
int	ft_check_duplicate(t_env *env, char *name);
int	find_and_replace(t_env *env, char *var);

#endif