/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malanglo <malanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:00:02 by malanglo          #+#    #+#             */
/*   Updated: 2024/09/16 14:41:20 by malanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	cmd_count(char **tokens)
{
	int	i;
	int	cmd_count;

	i = 0;
	cmd_count = 0;
	while (tokens[i] != NULL)
	{
		if (ft_strcmp(tokens[i], "|") == 0)
			cmd_count++;
		i++;
	}
	cmd_count++;
	return (cmd_count);
}

char	***malloc_cmds_array(char **tokens)
{
	int		nb_of_cmds;
	char	***cmds;
	int		i;

	nb_of_cmds = cmd_count(tokens);
	cmds = malloc(sizeof(char **) * (nb_of_cmds + 1));
	if (!cmds)
		return (NULL);
	i = 0;
	while (i < nb_of_cmds)
	{
		cmds[i] = NULL;
		i++;
	}
	cmds[i] = NULL;
	return (cmds);
}

static char	**create_command(char **tokens, int cur_start, int end)
{
	char	**cmd;
	int		i;

	cmd = malloc(sizeof(char *) * (end - cur_start + 1));
	if (!cmd)
		return (NULL);
	i = 0;
	while (i < (end - cur_start))
	{
		cmd[i] = ft_strdup(tokens[cur_start + i]);
		if (!cmd[i])
			return (NULL);
		i++;
	}
	cmd[end - cur_start] = NULL;
	return (cmd);
}

char	***create_cmds_array(char **tokens)
{
	char	***cmds;
	int		cur_start;
	int		token_index;
	int		cmd_index;

	cmds = malloc_cmds_array(tokens);
	cur_start = 0;
	token_index = 0;
	cmd_index = 0;
	while (tokens[token_index])
	{
		if (ft_strcmp(tokens[token_index], "|") == 0)
		{
			cmds[cmd_index] = create_command(tokens, cur_start, token_index);
			cmd_index++;
			cur_start = token_index + 1;
		}
		token_index++;
	}
	cmds[cmd_index] = create_command(tokens, cur_start, token_index);
	cmds[++cmd_index] = NULL;
	return (cmds);
}
