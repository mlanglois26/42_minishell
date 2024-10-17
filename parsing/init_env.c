/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malanglo <malanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:02:38 by malanglo          #+#    #+#             */
/*   Updated: 2024/09/15 16:30:28 by malanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_dup_env(char **envp)
{
	char	**dup_env;
	int		i;
	int		var_count;

	var_count = get_env_var_count(envp);
	dup_env = malloc(sizeof(char *) * (var_count + 1));
	if (!dup_env)
		return (NULL);
	i = 0;
	while (i < var_count)
	{
		dup_env[i] = ft_strdup(envp[i]);
		if (!dup_env[i])
		{
			free_double_pointer(dup_env);
			return (NULL);
		}
		i++;
	}
	dup_env[i] = NULL;
	return (dup_env);
}

int	check_if_env_i(void)
{
	char	*path;
	char	*home;

	path = getenv("PATH");
	home = getenv("HOME");
	if (path == NULL && home == NULL)
		return (1);
	return (0);
}

void	add_default_env_vars(char ***tmp_envp)
{
	char	*cmd[4];

	cmd[1] = "PWD=/home/malanglo/Documents/hell";
	export_cmd(cmd, tmp_envp);
	cmd[1] = "SHLVL=1";
	export_cmd(cmd, tmp_envp);
	cmd[1] = "PATH=/home/malanglo/bin:/home/malanglo/bin:/usr/local/sbin:/usr/local/bin:\
	/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin";
	export_cmd(cmd, tmp_envp);
	cmd[1] = "_=/usr/bin/env";
	export_cmd(cmd, tmp_envp);
}

void	init_and_configure_data(t_data *data, char **envp)
{
	*data = init_data(envp);
	data->eof_flag = 0;
	if (check_if_env_i() == 1)
		data->env_null = 1;
	if (data->env_null == 1)
	{
		add_default_env_vars(&data->tmp_envp);
		data->path_must_be_hidden = 1;
	}
}

void	init_ctrl_c(t_data *data)
{
	if (g_signal == 130)
		data->code_error = g_signal;
}
