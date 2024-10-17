/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malanglo <malanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 12:18:57 by malanglo          #+#    #+#             */
/*   Updated: 2024/08/09 11:56:17 by malanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	add_count_and_avance_de_1(int *count, int *i)
{
	(*count)++;
	(*i)++;
}

static void	add_count_and_avance_de_2(int *count, int *i)
{
	(*count)++;
	(*i) += 2;
}

int	operator_count(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '<' && line[i + 1] == '<')
			add_count_and_avance_de_2(&count, &i);
		else if (line[i] == '>' && line[i + 1] == '>')
			add_count_and_avance_de_2(&count, &i);
		else if (line[i] == '>')
			add_count_and_avance_de_1(&count, &i);
		else if (line[i] == '<')
			add_count_and_avance_de_1(&count, &i);
		else if (line[i] == '|')
			add_count_and_avance_de_1(&count, &i);
		else if (line[i] != '\0')
			i++;
	}
	return (count);
}

int	operator_found(char c)
{
	return (c == '|' || c == '>' || c == '<');
}
