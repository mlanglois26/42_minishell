/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malanglo <malanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 12:01:43 by malanglo          #+#    #+#             */
/*   Updated: 2024/08/13 11:20:53 by malanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	**malloc_tokens_array(char *line)
{
	char	**tokens;
	int		nb_of_tokens;
	int		i;

	nb_of_tokens = 0;
	nb_of_tokens = token_count(line);
	tokens = malloc(sizeof(char *) * (nb_of_tokens + 1));
	if (!tokens)
		return (NULL);
	i = 0;
	while (i < nb_of_tokens)
	{
		tokens[i] = NULL;
		i++;
	}
	tokens[i] = NULL;
	return (tokens);
}

static char	*copy_token(char *line, int cur_start, int cur_len)
{
	char	*token;
	int		k;

	token = malloc(sizeof(char) * (cur_len + 1));
	if (!token)
		return (NULL);
	k = 0;
	while (k < cur_len)
	{
		token[k] = line[cur_start + k];
		k++;
	}
	token[k] = '\0';
	return (token);
}

static int	quote_logic(char *line, int *i, int *inside_quote, char *quote_char)
{
	if (line[*i] == '\"' || line[*i] == '\'')
	{
		if (*inside_quote == 1 && line[*i] == *quote_char)
		{
			*inside_quote = 0;
			*quote_char = '\0';
		}
		else if (*inside_quote == 0)
		{
			*inside_quote = 1;
			*quote_char = line[*i];
		}
		return (1);
	}
	return (0);
}

static int	get_next_token(char *line, int *cur_start, int *cur_len, int *i)
{
	int		inside_quote;
	char	quote_char;

	inside_quote = 0;
	quote_char = '\0';
	while (line[*i] == 32 || line[*i] == 9)
		(*i)++;
	if (line[*i] == '\0')
		return (0);
	*cur_start = *i;
	while (line[*i] != '\0' && (line[*i] != 32 || inside_quote))
	{
		if (quote_logic(line, i, &inside_quote, &quote_char) == 1)
		{
			(*i)++;
			continue ;
		}
		(*i)++;
	}
	*cur_len = *i - *cur_start;
	return (1);
}

char	**get_token_array(char *line)
{
	char	**tokens;
	int		line_idx;
	int		token_idx;
	int		cur_start;
	int		cur_len;

	line_idx = 0;
	token_idx = 0;
	cur_start = 0;
	cur_len = 0;
	tokens = malloc_tokens_array(line);
	if (!tokens)
		return (NULL);
	while (get_next_token(line, &cur_start, &cur_len, &line_idx) != 0)
	{
		tokens[token_idx] = copy_token(line, cur_start, cur_len);
		token_idx++;
		line_idx = cur_start + cur_len;
	}
	tokens[token_idx] = NULL;
	return (tokens);
}
