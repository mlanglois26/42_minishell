/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   found.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malanglo <malanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 12:02:24 by malanglo          #+#    #+#             */
/*   Updated: 2024/09/14 16:26:53 by malanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	len_of_what_comes_after_dollar(char *token, int pos)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (token[i] != '\0')
	{
		if (token[i] == '$' && i == pos)
		{
			i++;
			while (token[i] != '\0')
			{
				len += 1;
				i++;
			}
			break ;
		}
		i++;
	}
	return (len);
}

char	*stock_what_comes_after_dollar(char *token, int pos)
{
	char	*found;

	int (i) = 0;
	int (k) = 0;
	int (len) = len_of_what_comes_after_dollar(token, pos);
	found = malloc(sizeof(char) * (len + 1));
	if (!found)
		return (NULL);
	while (token[i] != '\0')
	{
		if (token[i] == '$' && i == pos)
		{
			i++;
			while (token[i] != '\0')
			{
				found[k] = token[i];
				i++;
				k++;
			}
			break ;
		}
		i++;
	}
	found[k] = '\0';
	return (found);
}

int	compare_to_env_variables(char **envp, char *found)
{
	int		i;
	char	**split;

	i = 0;
	while (envp[i] != NULL)
	{
		split = ft_strsplit(envp[i], "=");
		if (ft_strncmp(split[0], found, ft_strlen(split[0])) == 0)
		{
			free_double_pointer(split);
			return (1);
		}
		else
			free_double_pointer(split);
		i++;
	}
	return (0);
}

int	this_token_has_a_dollar(char *token)
{
	int	i;

	i = 0;
	while (token[i] != '\0')
	{
		if (token[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

char	*get_envp_value(char **envp, char *found)
{
	int		i;
	char	**split;
	char	*value;

	i = 0;
	while (envp[i] != NULL)
	{
		split = ft_strsplit(envp[i], "=");
		if (ft_strncmp(split[0], found, ft_strlen(split[0])) == 0)
		{
			value = ft_strdup(split[1]);
			free_double_pointer(split);
			return (value);
		}
		free_double_pointer(split);
		i++;
	}
	return (NULL);
}
