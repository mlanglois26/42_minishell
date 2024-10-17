/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malanglo <malanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:14:13 by malanglo          #+#    #+#             */
/*   Updated: 2024/09/18 13:14:50 by malanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	big_free1(t_data *data)
{
	if (data->line)
	{
		free(data->line);
		data->line = NULL;
	}
	if (data->tokens)
	{
		free_double_pointer(data->tokens);
	}
	if (data->cmds)
	{
		free_triple_pointer(data->cmds);
	}
	if (data->original_envp)
	{
		free_double_pointer(data->original_envp);
	}
	if (data->tmp_envp)
	{
		free_double_pointer(data->tmp_envp);
		data->tmp_envp = NULL;
	}
	if (data->exe)
		free(data->exe);
}

void	null_cmd(char **cmd, t_data *data)
{
	if (cmd[0] == NULL)
	{
		error_printf("bash: command not found: %s\n", cmd[0]);
		data->code_error = 127;
		big_free1(data);
		exit(127);
	}
}
