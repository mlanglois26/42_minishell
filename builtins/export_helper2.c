/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malanglo <malanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:20:18 by malanglo          #+#    #+#             */
/*   Updated: 2024/09/16 14:26:29 by malanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	update_var_if_it_exists(char ***tmp_envp, char **split_var, char *new_val)
{
	int	i;

	i = 0;
	while ((*tmp_envp)[i] != NULL)
	{
		if (ft_strncmp((*tmp_envp)[i], split_var[0],
			ft_strlen(split_var[0])) == 0
			&& (*tmp_envp)[i][ft_strlen(split_var[0])] == '=')
		{
			free((*tmp_envp)[i]);
			(*tmp_envp)[i] = ft_strdup(new_val);
			return (1);
		}
		i++;
	}
	return (0);
}

void	add_new_var(char **new_envp, char *new_value)
{
	int	i;

	i = 0;
	while (new_envp[i] != NULL)
		i++;
	new_envp[i] = strdup(new_value);
	if (!new_envp[i])
	{
		free(new_envp);
		return ;
	}
	new_envp[i + 1] = NULL;
}

void	export_with_no_arg(char ***envp)
{
	int	i;

	i = 0;
	while ((*envp)[i] != NULL)
	{
		printf("export %s\n", (*envp)[i]);
		i++;
	}
}
