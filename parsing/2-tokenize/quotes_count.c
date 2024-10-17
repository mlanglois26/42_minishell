/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_count.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malanglo <malanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 12:28:58 by malanglo          #+#    #+#             */
/*   Updated: 2024/08/01 16:43:46 by malanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	find_first_quote(char *token, int start, char *quote_type)
{
	int	i;

	i = start;
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

int	find_next_quote(char *token, int start, char quote_type)
{
	int	i;

	i = start + 1;
	while (token[i] != '\0')
	{
		if (token[i] == quote_type)
			return (i);
		i++;
	}
	return (-1);
}

int	even_quote_pairs(char *token)
{
	char	quote_type;
	int		first;
	int		next;

	first = 0;
	next = 0;
	int (nb_of_quotes) = 0;
	int (i) = 0;
	while ((unsigned long)i < ft_strlen(token))
	{
		first = find_first_quote(token, i, &quote_type);
		if (first == -1)
			break ;
		i = first;
		nb_of_quotes++;
		next = find_next_quote(token, i, quote_type);
		if (next == -1)
			break ;
		i = next + 1;
		nb_of_quotes++;
	}
	if (nb_of_quotes % 2 == 0)
		return (1);
	else
		return (0);
}

int	handle_quotes_count(char **tokens, char *line)
{
	int	i;

	i = 0;
	while (tokens[i] != NULL)
	{
		if (even_quote_pairs(tokens[i]) == 0)
		{
			printf("Please, provide an even number of quotes.\n");
			free(line);
			free_double_pointer(tokens);
			tokens = NULL;
			return (0);
		}
		i++;
	}
	return (1);
}
