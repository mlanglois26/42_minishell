/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malanglo <malanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 10:41:06 by malanglo          #+#    #+#             */
/*   Updated: 2024/09/16 14:01:29 by malanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_cmd(char **cmd, char **envp, t_data *data)
{
	int	i;

	if (data->path_flag == 1)
	{
		printf("bash: env: No such file or directory\n");
		return (0);
	}
	if (!envp || cmd[1])
		return (-1);
	i = 0;
	while (envp[i])
	{
		if (data->path_must_be_hidden == 1 && ft_strncmp(envp[i], "PATH=",
				5) == 0)
			i++;
		printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}
