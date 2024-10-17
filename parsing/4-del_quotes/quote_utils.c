/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malanglo <malanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:28:42 by malanglo          #+#    #+#             */
/*   Updated: 2024/08/01 16:40:54 by malanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	quotes_must_be_deleted(char **tokens)
{
	int	i;
	int	j;

	i = 0;
	while (tokens[i] != NULL)
	{
		j = 0;
		while (tokens[i][j] != '\0')
		{
			if ((tokens[i][j] == 39) || (tokens[i][j] == 34))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	get_token_count(char **tokens)
{
	int	count;

	count = 0;
	while (tokens[count] != NULL)
	{
		count++;
	}
	return (count);
}

int	find_first_quote_type(char *token, char *quote_type)
{
	int	i;

	i = 0;
	while (token[i] != '\0')
	{
		if (token[i] == '\'' || token[i] == '\"')
		{
			*quote_type = token[i];
			return (i);
		}
		i++;
	}
	return (-1);
}
