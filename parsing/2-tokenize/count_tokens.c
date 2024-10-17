/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malanglo <malanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 12:06:14 by malanglo          #+#    #+#             */
/*   Updated: 2024/08/01 16:38:07 by malanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	handle_quotes(char *line, int *i)
{
	int		count;
	int		inside_quote;
	char	quote_char;

	count = 0;
	inside_quote = 0;
	if (line[*i] == '\'' || line[*i] == '\"')
	{
		quote_char = line[*i];
		inside_quote = 1;
		(*i)++;
		while (line[*i] != '\0' && (line[*i] != quote_char
				&& inside_quote == 1))
			(*i)++;
		if (line[*i] == quote_char)
			(*i)++;
		if (line[*i] == '\0' || line[*i] == 32 || line[*i] == 9)
			count++;
		inside_quote = 0;
	}
	return (count);
}

static int	handle_non_quotes(char *line, int *i)
{
	int		count;
	int		inside_quote;
	char	quote_char;

	count = 0;
	inside_quote = 0;
	while (line[*i] != '\0' && line[*i] != 32 && line[*i] != 9)
	{
		if (line[*i] == '\"' || line[*i] == '\'')
		{
			quote_char = line[*i];
			inside_quote = !inside_quote;
		}
		(*i)++;
	}
	count++;
	return (count);
}

int	token_count(char *line)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (line[i] != '\0')
	{
		while (line[i] == 32 || line[i] == 9)
			i++;
		if (line[i] == '\0')
			break ;
		count += handle_quotes(line, &i);
		count += handle_non_quotes(line, &i);
		if (line[i] != '\0')
			i++;
	}
	return (count);
}
