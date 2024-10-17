/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lens.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malanglo <malanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 12:32:07 by malanglo          #+#    #+#             */
/*   Updated: 2024/08/01 16:44:58 by malanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_key_len(char **envp, char *found)
{
	int		i;
	int		len;
	char	**split;

	i = 0;
	len = 0;
	while (envp[i] != NULL)
	{
		split = ft_strsplit(envp[i], "=");
		if (ft_strncmp(split[0], found, ft_strlen(split[0])) == 0)
		{
			len = ft_strlen(split[0]);
			free_double_pointer(split);
			break ;
		}
		else
			free_double_pointer(split);
		i++;
	}
	return (len);
}

int	len_of_what_comes_before_dollar(char *token, int pos)
{
	int	i;

	i = 0;
	while (token[i] != '\0')
	{
		if (token[i] == '$' && i == pos)
			break ;
		i++;
	}
	return (i);
}
