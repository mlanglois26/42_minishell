/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malanglo <malanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 12:35:06 by malanglo          #+#    #+#             */
/*   Updated: 2024/09/16 15:33:07 by malanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	dollar_found_in_array(char **tokens)
{
	int	i;
	int	j;

	i = 0;
	while (tokens[i] != NULL)
	{
		j = 0;
		while (tokens[i][j] != '\0')
		{
			if (tokens[i][j] == '$')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	count_single_quotes(char *line)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'')
			count++;
		i++;
	}
	return (count);
}

static void	get_single_quotes_positions_array(char *line, int **positions,
		int *count)
{
	int (i) = 0;
	int (in_quote) = 0;
	*count = count_single_quotes(line);
	*positions = (int *)malloc(sizeof(int) * (*count));
	if (*positions == NULL)
	{
		*count = 0;
		return ;
	}
	i = 0;
	*count = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'')
		{
			(*positions)[(*count)++] = i;
			in_quote = !in_quote;
		}
		i++;
	}
}

int	this_dollar_is_inside_single_quotes_improved(char *line, int pos)
{
	int	start;
	int	end;
	int	*positions;

	int (count) = 0;
	int (i) = 0;
	positions = NULL;
	get_single_quotes_positions_array(line, &positions, &count);
	if (positions == NULL || count <= 0)
		return (free(positions), 0);
	while (i < count - 1)
	{
		start = positions[i];
		end = positions[i + 1];
		if (pos > start && pos < end)
		{
			free(positions);
			positions = NULL;
			return (1);
		}
		i += 2;
	}
	free(positions);
	positions = NULL;
	return (0);
}
