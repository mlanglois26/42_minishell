/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_filter1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malanglo <malanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:54:43 by malanglo          #+#    #+#             */
/*   Updated: 2024/09/17 13:21:28 by malanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	boucle(char **original_envp, char *var)
{
	int	i;

	i = 0;
	while (original_envp[i] != NULL)
	{
		if (ft_strncmp(original_envp[i], var, ft_strlen(var)) == 0
			&& original_envp[i][ft_strlen(var)] == '=')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	var_has_been_del_from_original_envp(char **original_envp,
		char **current_envp, char *var)
{
	int	i;
	int	found_in_original;
	int	found_in_current;

	found_in_original = 0;
	found_in_current = 0;
	if (var[0] == '$')
		var++;
	if (boucle(original_envp, var) == 1)
		found_in_original = 1;
	i = 0;
	while (current_envp[i] != NULL)
	{
		if (ft_strncmp(current_envp[i], var, ft_strlen(var)) == 0
			&& current_envp[i][ft_strlen(var)] == '=')
		{
			found_in_current = 1;
			break ;
		}
		i++;
	}
	return (found_in_original + found_in_current);
}

int	echo_nothing(t_data *data)
{
	if (data->cmds[0][1] == NULL)
	{
		printf("\n");
		return (1);
	}
	return (0);
}

void	echo_filter(t_data *data, char **cmd)
{
	if (echo_nothing(data) == 1)
		return ;
	if (ft_strcmp(data->cmds[0][1], "$?") == 0)
	{
		printf("%d\n", g_signal);
		return ;
	}
	if (data->cmds[0][1] && (data->original_envp == NULL))
	{
		error_printf("bash: %s: command not found\n", cmd[0]);
		data->code_error = 127;
		return ;
	}
	else if (data->is_exported_flag)
		data->code_error = echo_cmd(cmd);
	else if (data->cmds[0][1]
		&& var_has_been_del_from_original_envp(data->original_envp,
			data->tmp_envp, data->cmds[0][1]) == 1)
	{
		data->code_error = 0;
		printf("\n");
	}
	else
		data->code_error = echo_cmd(cmd);
}
