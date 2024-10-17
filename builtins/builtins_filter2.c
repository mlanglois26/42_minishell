/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_filter2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malanglo <malanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:10:18 by malanglo          #+#    #+#             */
/*   Updated: 2024/09/19 17:43:13 by malanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_unseted_var(t_data *data, int *i)
{
	if (ft_strcmp(data->cmds[0][*i], "HOME") == 0)
		data->home_flag = 1;
	if (ft_strcmp(data->cmds[0][*i], "OLDPWD") == 0)
		data->oldpwd_flag = 1;
}

void	unset_filter(t_data *data, char **cmd)
{
	int	i;

	i = 0;
	if (!data->cmds[0][1])
		return ;
	while (cmd[i] != NULL)
	{
		if (ft_strcmp(data->cmds[0][i], "PATH") == 0)
		{
			data->path_flag = 1;
			data->code_error = 0;
		}
		handle_unseted_var(data, &i);
		if (data->path_flag == 0)
			data->code_error = unset_cmd(cmd, &data->tmp_envp);
		if (data->path_flag == 1)
			data->code_error = unset_cmd(cmd, &data->safe_envp);
		i++;
	}
}

void	export_filter(t_data *data, char **cmd)
{
	data->is_exported_flag = 1;
	data->code_error = export_cmd(cmd, &(data->tmp_envp));
}

void	unset_without_env(t_data *data)
{
	data->safe_envp = get_dup_env(data->tmp_envp);
	if (data->tmp_envp != NULL)
	{
		free_double_pointer(data->tmp_envp);
		data->tmp_envp = NULL;
	}
	data->tmp_envp = data->safe_envp;
}
