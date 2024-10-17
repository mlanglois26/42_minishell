/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malanglo <malanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:44:41 by malanglo          #+#    #+#             */
/*   Updated: 2024/09/16 14:21:37 by malanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A'
			&& c <= 'Z'))
		return (1);
	else
		return (0);
}

int	is_valid_var_name(const char *var_name)
{
	int	i;

	if (!var_name || (!ft_isalpha(var_name[0]) && var_name[0] != '_'))
		return (0);
	i = 1;
	while (var_name[i])
	{
		if (!ft_isalnum(var_name[i]) && var_name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

char	**ft_realloc(char **envp, int add_one_size)
{
	int		i;
	int		cur_size;
	char	**new_envp;

	cur_size = get_env_var_count(envp);
	new_envp = malloc(sizeof(char *) * (cur_size + add_one_size + 1));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (i < cur_size)
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
		{
			free_double_pointer(new_envp);
			return (NULL);
		}
		i++;
	}
	new_envp[cur_size] = NULL;
	free_double_pointer(envp);
	return (new_envp);
}
