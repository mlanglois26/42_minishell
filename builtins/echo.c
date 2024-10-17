/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malanglo <malanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 10:40:03 by malanglo          #+#    #+#             */
/*   Updated: 2024/09/15 11:07:12 by malanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo_logic(char **cmd, int *i, int *option_flag)
{
	int	j;

	while (cmd[*i] != NULL && cmd[*i][0] == '-')
	{
		j = 1;
		while (cmd[*i][j] == 'n')
			j++;
		if (cmd[*i][j] == '\0')
		{
			(*option_flag) = 1;
			(*i)++;
		}
		else
			break ;
	}
}

int	echo_cmd(char **cmd)
{
	int	i;
	int	option_flag;

	i = 1;
	option_flag = 0;
	if (cmd == NULL || cmd[0] == NULL)
		return (-1);
	echo_logic(cmd, &i, &option_flag);
	while (cmd[i] != NULL)
	{
		printf("%s", cmd[i]);
		if (cmd[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (option_flag == 0)
		printf("\n");
	return (0);
}
