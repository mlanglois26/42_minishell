/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malanglo <malanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 10:41:20 by malanglo          #+#    #+#             */
/*   Updated: 2024/09/18 09:48:50 by malanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_atoi(const char *nptr, long long int *res)
{
	int	sign;
	int	i;

	*res = 0;
	sign = 1;
	i = 0;
	while ((nptr[i] == 32) || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+')
		i++;
	else if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	while ((nptr[i] >= '0' && nptr[i] <= '9'))
	{
		if (__LONG_LONG_MAX__ / 10 < *res || (*res == __LONG_LONG_MAX__ / 10
				&& nptr[i] - 48 > __LONG_LONG_MAX__ % 10))
			return (1);
		*res = *res * 10 + (nptr[i] - '0');
		i++;
	}
	*res = sign * *res % 256;
	return (0);
}

int	is_numeric(const char *str)
{
	int	i;
	int	sign;
	int	has_digit;

	sign = 0;
	has_digit = 0;
	i = 0;
	while (str[i] == ' ')
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		sign++;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		has_digit = 1;
		i++;
	}
	if (str[i] != '\0' || has_digit == 0 || sign > 1)
		return (1);
	return (0);
}

void	logic_exit_cmd(t_data *data, char **cmd, long long int exit_code)
{
	printf("bash: exit: %s: numeric argument required\n", cmd[1]);
	exit_code = 2;
	big_free(data);
	exit(exit_code);
}

int	exit_cmd(char **cmd, t_data *data)
{
	long long int (exit_code) = 0;
	printf("exit\n");
	if (cmd[1] != NULL)
	{
		if (is_numeric(cmd[1]) == 0)
		{
			if (ft_atoi(cmd[1], &exit_code) == 1)
			{
				printf("bash: exit: %s: numeric argument required\n", cmd[1]);
				exit_code = 2;
				big_free(data);
				exit(exit_code);
			}
			if (cmd[2] != NULL)
			{
				printf("bash: exit: too many arguments\n");
				return (1);
			}
		}
		else
			logic_exit_cmd(data, cmd, exit_code);
	}
	big_free(data);
	exit(exit_code);
}
