/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_clean_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malanglo <malanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 12:22:51 by malanglo          #+#    #+#             */
/*   Updated: 2024/09/17 16:37:44 by malanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// faire un strcmptp car pb pour <>

static void	logic_modif(char *line, char *modified_line, int *i, int *j)
{
	if (operator_found(line[*i]) && (line[(*i) + 1] == '>' || line[(*i)
				+ 1] == '<'))
	{
		modified_line[(*j)++] = ' ';
		modified_line[(*j)++] = line[*i];
		modified_line[(*j)++] = line[*i];
		modified_line[(*j)++] = ' ';
		(*i) += 2;
	}
	else if (operator_found(line[*i]))
	{
		modified_line[(*j)++] = ' ';
		modified_line[(*j)++] = line[*i];
		modified_line[(*j)++] = ' ';
		(*i)++;
	}
	else
		modified_line[(*j)++] = line[(*i)++];
}

static int	this_operator_is_inside_quotes(char *line, int pos)
{
	int	start;
	int	end;

	start = 0;
	end = 0;
	get_single_quotes_positions(line, &start, &end);
	if (pos > start && pos < end)
		return (1);
	get_double_quotes_positions(line, &start, &end);
	if (pos > start && pos < end)
		return (1);
	return (0);
}

static char	*modify_input_line(char *line, int count)
{
	char	*modified_line;

	int (i) = 0;
	int (j) = 0;
	int (size) = ft_strlen(line);
	modified_line = malloc(sizeof(char) * (size + (count * 2) + 1));
	if (!modified_line)
		return (NULL);
	while (line[i] != '\0')
	{
		if (operator_found(line[i]) && !this_operator_is_inside_quotes(line, i))
			logic_modif(line, modified_line, &i, &j);
		else
			modified_line[j++] = line[i++];
	}
	modified_line[j] = '\0';
	if (strcmp(modified_line, line) == 0)
		line = modified_line;
	return (modified_line);
}

char	*modify_line(char *line)
{
	int		count;
	char	*modified_line;

	count = operator_count(line);
	if (count > 0)
	{
		modified_line = modify_input_line(line, count);
		free(line);
	}
	else
		modified_line = line;
	return (modified_line);
}
