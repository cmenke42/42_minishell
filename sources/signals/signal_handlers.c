/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 11:48:04 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/01 12:17:36 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_handle_sigint_in_parent_during_execution(int sig_num)
{
	g_signal_number = sig_num;
	rl_replace_line("", 1);
	write(1, "\n", 1);
	rl_on_new_line();
}

void	ft_handle_sigquit_in_parent_during_execution(int sig_num)
{
	g_signal_number = sig_num;
	rl_replace_line("", 1);
	write(1, "\n", 1);
	rl_on_new_line();
}

//handles the ctrl-C key during execution of a command in the parent process
// rl_replace_line(PROMPT, 1); -> 1 clears the undo list
// of the current line (cmd z)
void	ft_handle_sigint_in_minishell(int sig_num)
{
	g_signal_number = sig_num;
	rl_replace_line("", 1);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}
