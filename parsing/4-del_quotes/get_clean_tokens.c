/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_clean_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malanglo <malanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 12:37:28 by malanglo          #+#    #+#             */
/*   Updated: 2024/08/01 16:45:15 by malanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	*get_quote_positions(char *token, int *count)
{
	int		*positions;
	char	quote_type;
	int		first;
	int		next;

	int (nb_of_quotes) = 0;
	int (i) = 0;
	positions = malloc(sizeof(int) * ft_strlen(token));
	if (!positions)
		return (NULL);
	while ((unsigned long)i < ft_strlen(token))
	{
		first = find_first_quote_type(&token[i], &quote_type);
		if (first == -1)
			break ;
		first += i;
		positions[nb_of_quotes++] = first;
		next = find_next_quote(token, i, quote_type);
		if (next == -1)
			break ;
		i = next + 1;
		positions[nb_of_quotes++] = next;
	}
	*count = nb_of_quotes;
	return (positions);
}

static void	get_clean_token_logic(char *token, char *clean_token,
		int *quote_indice, int nb_of_quotes)
{
	int (is_quote);
	int (q);
	int (len) = ft_strlen(token);
	int (j) = 0;
	int (i) = 0;
	while (i < len)
	{
		is_quote = 0;
		q = 0;
		while (q < nb_of_quotes)
		{
			if (i == quote_indice[q])
			{
				is_quote = 1;
				break ;
			}
			q++;
		}
		if (is_quote == 0)
			clean_token[j++] = token[i];
		i++;
	}
	clean_token[j] = '\0';
}

static char	*get_clean_token(char *token)
{
	int		nb_of_quotes;
	int		*quote_indice;
	int		len;
	char	*clean_token;

	quote_indice = get_quote_positions(token, &nb_of_quotes);
	if (!quote_indice)
		return (NULL);
	len = ft_strlen(token);
	clean_token = malloc(sizeof(char) * (len + 1));
	if (!clean_token)
	{
		free(quote_indice);
		return (NULL);
	}
	get_clean_token_logic(token, clean_token, quote_indice, nb_of_quotes);
	free(quote_indice);
	return (clean_token);
}

char	**return_tokens_without_quotes(char **tokens)
{
	int		token_count;
	char	**clean_tokens;
	int		i;

	token_count = get_token_count(tokens);
	clean_tokens = malloc(sizeof(char *) * (token_count + 1));
	if (!clean_tokens)
		return (NULL);
	i = 0;
	while (i < token_count)
	{
		clean_tokens[i] = get_clean_token(tokens[i]);
		if (!clean_tokens[i])
		{
			free_double_pointer(clean_tokens);
			return (NULL);
		}
		i++;
	}
	clean_tokens[i] = NULL;
	free_double_pointer(tokens);
	return (clean_tokens);
}
