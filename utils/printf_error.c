/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malanglo <malanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 10:36:32 by malanglo          #+#    #+#             */
/*   Updated: 2024/09/17 10:37:08 by malanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_printf(const char *format, const char *str)
{
	int	i;

	i = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1] == 's')
		{
			if (str)
				write(2, str, ft_strlen(str));
			i++;
		}
		else
			write(2, &format[i], 1);
		i++;
	}
}
