/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malanglo <malanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 10:40:55 by malanglo          #+#    #+#             */
/*   Updated: 2024/09/16 14:01:00 by malanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_env_var_count(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	return (i);
}

int	is_var_to_remove(char *env_var, char *my_var)
{
	char	**key_val;
	int		result;

	key_val = ft_strsplit(env_var, "=");
	result = 0;
	if (key_val)
	{
		if (ft_strcmp(key_val[0], my_var) == 0)
			result = 1;
		free_double_pointer(key_val);
	}
	return (result);
}

int	is_var_in_env(char *my_var, char **envp)
{
	int		i;
	char	**key_val;

	i = 0;
	while (envp[i] != NULL)
	{
		key_val = ft_strsplit(envp[i], "=");
		if (key_val)
		{
			if (ft_strcmp(key_val[0], my_var) == 0)
			{
				free_double_pointer(key_val);
				return (1);
			}
			free_double_pointer(key_val);
		}
		i++;
	}
	return (0);
}

void	unset_heart(char **cmd, int i, char ***envp)
{
	int	j;

	j = 0;
	while ((*envp)[j] != NULL)
	{
		if (is_var_to_remove((*envp)[j], cmd[i]))
		{
			free((*envp)[j]);
			while ((*envp)[j] != NULL)
			{
				(*envp)[j] = (*envp)[j + 1];
				j++;
			}
			break ;
		}
		j++;
	}
}

int	unset_cmd(char **cmd, char ***envp)
{
	int	i;

	if (*envp == NULL || cmd[1] == NULL)
		return (-1);
	i = 1;
	while (cmd[i] != NULL)
	{
		if (is_var_in_env(cmd[i], *envp) == 0)
		{
			i++;
			continue ;
		}
		unset_heart(cmd, i, envp);
		i++;
	}
	return (0);
}
