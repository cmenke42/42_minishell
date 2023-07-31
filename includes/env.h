/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 11:38:04 by wmoughar          #+#    #+#             */
/*   Updated: 2023/07/31 19:03:26 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "minishell.h"
typedef struct s_env
{
	char			*name;
	char			*value;
	bool			print_empty_quotes;
	struct s_env	*next;
}	t_env;

//env
void	ft_print_one_env_variable(t_env *env_variable);
void	ft_print_env_list(t_list *env_list);

//export
int	ft_update_or_add_env_variable(char *argument, t_list **env_list, char *name, char *value);
t_list	*ft_search_for_env_variable(char *argument, t_list *env_list);

//print export
int	ft_export(char **arguemnts, t_list **env_list);
int	print_export(t_list **env_list);
t_list	*ft_sort_list_asci(t_list *lst);
void	ft_swap(void **var1, void **var2);
void *ft_duplicate_env_variable(void *env_variable);

//unset
int	ft_unset(char **arguments, t_list **env_list_new, t_shell_data *shell_data);
void 	ft_lstremove(t_list **env_list, t_list *env_variable_to_remove);

// //pwd
int	ft_pwd(char **pwd, bool print);
void	ft_print_pwd_and_free(char *path);
//exit
void	ft_exit(char **args, t_shell_data *shell_data);
int	ft_exit_code(char *str, bool *print_exit);
bool	ft_get_number(char *str, int *exit_code);

//echo
void	ft_echo(char **command);
void	print_lines(int i, char **str);


//cd
int	ft_cd(char **command, t_list **env_list, t_shell_data *shell_data);
int	ft_put_err(char *input, char *message, int code);
int	change_dir(t_list **env_list, char *target_path, t_shell_data *shell_data);
int	cd_error_handler(char *dir, t_list *env_variable_pwd);
// int	replace_pwd(t_list *env_variable_pwd, char *dir);

// //utils
// t_env	*ft_search(t_env *env, char *name);
// t_env	*update_value(t_env *env, char *name, char *new_val);
// int		ft_put_err(char *input, char *message, int code);

//new_export
int		ft_store_env_in_list(char **env, t_list **env_list);
int		ft_store_one_variable_in_node(t_list **env_list, char *name, char *value, char *equal_sign);
int		ft_create_name_and_value(char *argument, char **name, char **value, char *equal_sign);
bool	ft_is_syntax_error_in_env_name(char *string);
void	ft_assign_name_and_value_to_env_variable(t_env *env_variable, char *name, char *value, char *equal_sign);
void	ft_print_export_wrong_identifier(char *argument);

#endif