/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malanglo <malanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:32:59 by malanglo          #+#    #+#             */
/*   Updated: 2024/09/19 16:37:09 by malanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*ft_extract_path(char **env)
{
	int	i;

	if (!env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (ft_strdup(env[i] + 5));
		i++;
	}
	return (NULL);
}

char	*ft_cmd_path(const char *cmd_name, char **env)
{
	char	*path;
	char	*full_path;
	char	*cmd_path;
	char	**directories;

	int (i) = -1;
	path = ft_extract_path(env);
	if (!path)
		return (NULL);
	directories = ft_strsplit(path, ":");
	free(path);
	while (directories[++i])
	{
		full_path = ft_strjoin(directories[i], "/");
		cmd_path = ft_strjoin(full_path, cmd_name);
		free(full_path);
		if (access(cmd_path, X_OK) == 0)
		{
			ft_free_tab(directories);
			return (cmd_path);
		}
		free(cmd_path);
	}
	ft_free_tab(directories);
	return (NULL);
}

void	ft_absolute_cmd(char **cmd, char **envp, t_data *data)
{
	if (access(cmd[0], X_OK) == 0)
	{
		if (execve(cmd[0], cmd, envp) == -1)
		{
			printf("Failed to execute\n");
			data->code_error = 127;
			big_free(data);
			exit(127);
		}
		exit(0);
	}
	else
	{
		error_printf("bash: command not found: %s\n", cmd[0]);
		data->code_error = 127;
		big_free(data);
		exit(127);
	}
}

void	ft_execute_command(char **cmd, t_data *data)
{
	char	*cmd_path;

	null_cmd(cmd, data);
	cmd_path = ft_cmd_path(cmd[0], data->tmp_envp);
	if (!cmd_path)
	{
		if (cmd[0] != NULL && ft_strcmp(cmd[0], "$?") == 0)
		{
			data->code_error = 127;
			return ;
		}		
		error_printf("bash: command not found: %s\n", cmd[0]);
		data->code_error = 127;
		big_free1(data);
		free(cmd_path);
		exit(127);
	}
	if (execve(cmd_path, cmd, data->tmp_envp) == -1)
	{
		free(cmd_path);
		exit(1);
	}
	free(cmd_path);
	exit(0);
}
