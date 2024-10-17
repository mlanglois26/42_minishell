/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malanglo <malanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 12:13:20 by malanglo          #+#    #+#             */
/*   Updated: 2024/08/01 16:41:09 by malanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	get_single_quotes_positions(char *line, int *start, int *end)
{
	int	i;

	i = 0;
	*start = -1;
	*end = -1;
	while (line[i] != '\0')
	{
		if (line[i] == '\'')
		{
			*start = i;
			if (line[i] != '\0')
				i++;
			while (line[i] != '\0' && line[i] != '\'')
				i++;
			if (line[i] == '\'')
			{
				*end = i;
				break ;
			}
		}
		if (line[i] != '\0')
			i++;
	}
}

void	get_double_quotes_positions(char *line, int *start, int *end)
{
	int	i;

	i = 0;
	*start = -1;
	*end = -1;
	while (line[i] != '\0')
	{
		if (line[i] == '\"')
		{
			*start = i;
			if (line[i] != '\0')
				i++;
			while (line[i] != '\0' && line[i] != '\"')
				i++;
			if (line[i] == '\"')
			{
				*end = i;
				break ;
			}
		}
		if (line[i] != '\0')
			i++;
	}
}

static int	this_operator_is_inside_single_quotes(char *line)
{
	int	i;
	int	pos;
	int	start;
	int	end;

	i = 0;
	pos = 0;
	start = 0;
	end = 0;
	while (line[i] != '\0')
	{
		if (operator_found(line[i]))
			pos = i;
		if (line[i] != '\0')
			i++;
	}
	get_single_quotes_positions(line, &start, &end);
	if (pos > start && pos < end)
		return (1);
	return (0);
}

static int	this_operator_is_inside_double_quotes(char *line)
{
	int	i;
	int	pos;
	int	start;
	int	end;

	i = 0;
	pos = 0;
	start = 0;
	end = 0;
	while (line[i] != '\0')
	{
		if (operator_found(line[i]))
			pos = i;
		if (line[i] != '\0')
			i++;
	}
	get_double_quotes_positions(line, &start, &end);
	if (pos > start && pos < end)
		return (1);
	return (0);
}

int	all_operators_are_inside_quotes(char *line)
{
	int	flag;
	int	op_count;
	int	i;

	flag = 0;
	op_count = operator_count(line);
	i = 0;
	while (line[i] != '\0')
	{
		if (this_operator_is_inside_single_quotes(line) == 1)
			flag++;
		if (this_operator_is_inside_double_quotes(line) == 1)
			flag++;
		i++;
	}
	if (flag == op_count)
		return (1);
	return (0);
}
