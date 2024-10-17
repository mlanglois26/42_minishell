/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_clean.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malanglo <malanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:54:41 by malanglo          #+#    #+#             */
/*   Updated: 2024/09/19 16:40:11 by malanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_double_pointer(char **ptr)
{
	int	i;

	if (ptr == NULL)
		return ;
	i = 0;
	while (ptr[i] != NULL)
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

void	free_triple_pointer(char ***ptr)
{
	int	i;
	int	j;

	if (ptr == NULL)
		return ;
	i = 0;
	while (ptr[i] != NULL)
	{
		j = 0;
		while (ptr[i][j] != NULL)
		{
			free(ptr[i][j]);
			j++;
		}
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

void	clean_1(t_data *data)
{
	free(data->line);
	free_double_pointer(data->tokens);
	free_triple_pointer(data->cmds);
}

void	clean_2(t_data *data)
{
	free_double_pointer(data->original_envp);
	if (data->path_flag == 1)
		free_double_pointer(data->safe_envp);
	if (data->tmp_envp != NULL)
	{
		free_double_pointer(data->tmp_envp);
		data->tmp_envp = NULL;
	}
	free(data->exe);
}

void	big_free(t_data *data)
{
	free(data->line);
	free_double_pointer(data->tokens);
	free_triple_pointer(data->cmds);
	free_double_pointer(data->original_envp);
	if (data->safe_envp != NULL)
	{
		free_double_pointer(data->safe_envp);
		data->safe_envp = NULL;
	}
	if (data->tmp_envp != NULL)
	{
		free_double_pointer(data->tmp_envp);
		data->tmp_envp = NULL;
	}
	free(data->exe);
}
