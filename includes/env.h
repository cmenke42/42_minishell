/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 11:38:04 by wmoughar          #+#    #+#             */
/*   Updated: 2023/08/04 22:50:41 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "minishell.h"

//cd
int		ft_cd(char **command, t_list **env_list, t_shell_data *shell_data);
int		ft_put_err(char *input, char *message, int code);
int		change_dir(t_list **env_list, char *target_path,
			t_shell_data *shell_data);
int		cd_error_handler(char *dir, t_list *env_variable_pwd);
bool	store_var_in_node(t_list **env_list, char *name,
	char *value, bool print_empty_quotes);
bool	ft_create_name_and_value(char *argument, char **name,
	char **value, bool *print_empty_quotes);
int		ft_substr_value(char **value, char **name,
			char *equal_sign, int value_len);
bool	ft_is_syntax_error_in_env_name(char *string);
void	ft_assign(t_env *env_variable,
	char *name, char *value, bool print_empty_quotes);
void	ft_print_export_wrong_identifier(char *argument);
//echo
void	ft_echo(char **command);
//env
void	ft_print_env_list(t_list *env_list);
//exit
void	ft_exit(char **args, t_shell_data *shell_data);
//export
int		ft_update_or_add_env_variable(char *argument, t_list **env_list,
			char *name, char *value);
t_list	*ft_search_for_env_variable(char *argument, t_list *env_list);
void	ft_free_name_and_value(char **name, char **value);
//print export
int		ft_export(char **arguemnts, t_list **env_list);
int		print_export(t_list **env_list);
// //pwd
int		ft_pwd(char **pwd, bool print);
void	ft_print_pwd_and_free(char *path);
//unset
int		ft_unset(char **arguments, t_list **env_list_new,
			t_shell_data *shell_data);

#endif