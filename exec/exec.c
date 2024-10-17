/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malanglo <malanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:28:00 by malanglo          #+#    #+#             */
/*   Updated: 2024/09/19 10:26:22 by malanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_cmds(t_data *data)
{
	int	i;

	i = 0;
	while (data->cmds[i])
		i++;
	return (i);
}

int	ft_is_builtin(char *cmd)
{
	if (cmd)
	{
		if (ft_strcmp(cmd, "echo") == 0)
			return (1);
		else if (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "~") == 0)
			return (1);
		else if (ft_strcmp(cmd, "pwd") == 0)
			return (1);
		else if (ft_strcmp(cmd, "export") == 0)
			return (1);
		else if (ft_strcmp(cmd, "unset") == 0)
			return (1);
		else if (ft_strcmp(cmd, "env") == 0)
			return (1);
		else if (ft_strcmp(cmd, "exit") == 0)
			return (1);
	}
	return (0);
}

void	ft_exec_builtin(t_data *data, char **cmd)
{
	if (ft_strcmp(cmd[0], "echo") == 0)
		echo_filter(data, cmd);
	else if (ft_strcmp(cmd[0], "cd") == 0 || ft_strcmp(cmd[0], "~") == 0)
		data->code_error = cd_cmd(cmd, data);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		data->code_error = pwd_cmd();
	else if (ft_strcmp(cmd[0], "export") == 0)
		export_filter(data, cmd);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		unset_filter(data, cmd);
	else if (ft_strcmp(cmd[0], "env") == 0)
		data->code_error = env_cmd(cmd, data->tmp_envp, data);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		data->code_error = exit_cmd(cmd, data);
	g_signal = data->code_error;
}

void	ft_init_exe(t_data *data, int is_last_cmd)
{
	if (!is_last_cmd && pipe(data->exe->pipe_fd) == -1)
		exit(1);
	data->exe->pid = fork();
	data->exe->n_fork++;
	if (data->exe->pid == -1)
		exit(1);
}

int	builtin_cmd(t_data *data, int saved_stdout)
{
	int	j;

	j = 0;
	while (data->cmds[0][j])
	{
		if (handle_redir_output_special(data, saved_stdout, j))
			return (1);
		if (handle_redir_append_special(data, saved_stdout, j))
			return (1);
		j++;
	}
	return (0);
}
