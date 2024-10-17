/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malanglo <malanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 10:40:41 by malanglo          #+#    #+#             */
/*   Updated: 2024/09/16 14:21:18 by malanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	validate_var(char **split_var, char *cmd_arg)
{
	if (!split_var || split_var[0] == NULL)
	{
		printf("export: '%s': not a valid identifier\n", cmd_arg);
		return (0);
	}
	if (!is_valid_var_name(split_var[0]))
	{
		printf("export: '%s': not a valid identifier\n", cmd_arg);
		return (0);
	}
	return (1);
}

int	handle_no_argument(char ***tmp_envp, char **cmd)
{
	if (cmd[1] == NULL)
	{
		export_with_no_arg(tmp_envp);
		return (1);
	}
	return (0);
}

int	update_or_add_var(char ***tmp_envp, char **split_var, char *cmd_arg)
{
	int		var_exists;
	char	**new_envp;

	var_exists = update_var_if_it_exists(tmp_envp, split_var, cmd_arg);
	if (var_exists == 0)
	{
		new_envp = ft_realloc(*tmp_envp, 1);
		if (!new_envp)
			return (-1);
		add_new_var(new_envp, cmd_arg);
		*tmp_envp = new_envp;
	}
	return (0);
}

int	handle_export_var(char *cmd_arg, char ***tmp_envp)
{
	char	**split_var;

	split_var = ft_strsplit(cmd_arg, "=");
	if (!split_var || split_var[1] == NULL)
	{
		free_double_pointer(split_var);
		return (0);
	}
	if (!validate_var(split_var, cmd_arg))
	{
		free_double_pointer(split_var);
		return (0);
	}
	if (update_or_add_var(tmp_envp, split_var, cmd_arg) == -1)
	{
		free_double_pointer(split_var);
		return (-1);
	}
	free_double_pointer(split_var);
	return (0);
}

int	export_cmd(char **cmd, char ***tmp_envp)
{
	int	i;

	if (handle_no_argument(tmp_envp, cmd) == 1)
		return (0);
	i = 1;
	while (cmd[i] != NULL)
	{
		if (handle_export_var(cmd[i], tmp_envp) == -1)
			return (-1);
		i++;
	}
	return (0);
}
