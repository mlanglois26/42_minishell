/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malanglo <malanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 11:29:42 by malanglo          #+#    #+#             */
/*   Updated: 2024/09/17 11:46:20 by malanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_child(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 130;
		printf("\n");
	}
}

void	sigquit_child(int sig)
{
	if (sig == SIGQUIT)
	{
		g_signal = 131;
		printf("Quit (core dumped)\n");
	}
}

void	signal_handler_child(void)
{
	signal(SIGINT, sigint_child);
	signal(SIGQUIT, sigquit_child);
}

void	sigint_parent(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 130;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signal_handler_parent(void)
{
	signal(SIGINT, sigint_parent);
	signal(SIGQUIT, SIG_IGN);
}
