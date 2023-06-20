/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmoughar <wmoughar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 11:38:04 by wmoughar          #+#    #+#             */
/*   Updated: 2023/06/20 19:07:15 by wmoughar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct	s_env
{
	char	*value;
	struct s_env	*next;
}	t_env;

int		ft_env_len(char **env);
char	**sort_env(char **env, int env_len);
int main(int argc, char **argv, char **env);
void	export(char **envp);
void	print_env(char **envp);

#endif