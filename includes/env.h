/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 11:38:04 by wmoughar          #+#    #+#             */
/*   Updated: 2023/07/26 18:32:48 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "minishell.h"
typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

//env
t_env	*ft_create_node(char *name, char *value);
void	print_env(t_env *envp);
t_env	*store_env(char **env);

//export
void	export(t_env *envp);
t_env	*sort_env(t_env *env);
int		ft_check_name(char *name);
int		ft_check_name_start(char *s);
int		ft_check_duplicate(t_env *env, char *name, char *new_name);
t_env	*add_to_list(t_env *head, char *var);
t_env	*find_and_replace(t_env *env, t_env *new);
void	ft_export(char **command, t_env *env);

//unset
void    ft_unset(char **command, t_env *env);

//free
void	free_split(char **arr);
void	free_env(t_env *env);

//pwd
int		ft_pwd(void);

//exit
void	ft_exit(char **args);

//echo
int	ft_echo(char **command);


//cd
int	ft_cd(char **command, t_env *env);
void	ft_add_to_list(t_env *head, t_env *newnode);
int	cd_error_handler(char *dir);

//utils
t_env	*ft_search(t_env *env, char *name);
t_env	*update_value(t_env *env, char *name, char *new_val);
char 	*reverse_split(const char *name, const char *value);
int		ft_put_err(char *input, char *message, int code);

//new_export
int		ft_store_env_in_list(char **env, t_list **env_list);
int		ft_store_one_variable_in_node(t_list **env_list, char *argument, bool first_import);
int		ft_assign_values_to_env_variable_node(t_env *env_variable, char *argument, bool first_import);
int		ft_create_name_and_value(char *argument, char **name, char **value, char *equal_sign);
bool	ft_is_syntax_error_in_env_name(char *string, char *equal_sign, bool first_import);
void	ft_assig_name_and_value_to_env_variable(t_env *env_variable, char *name, char *value);
void	ft_print_export_wrong_identifier(char *argument);

#endif