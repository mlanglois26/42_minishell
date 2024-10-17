/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malanglo <malanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:42:32 by malanglo          #+#    #+#             */
/*   Updated: 2024/09/19 15:35:51 by malanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_code_error(t_data *data)
{
	int	status;
	int	i;

	i = 0;
	while (i < data->exe->n_fork)
	{
		waitpid(-1, &status, 0);
		i++;
	}
	if (WIFEXITED(status))
	{
		data->code_error = WEXITSTATUS(status);
		g_signal = data->code_error;
	}
	else if (WIFSIGNALED(status))
	{
		data->code_error = 128 + WTERMSIG(status);
		g_signal = data->code_error;
	}
}

int	cmd_special(t_data *data)
{
	if (data->cmds[0][0] != NULL && ft_strcmp(data->cmds[0][0], "$?") == 0)
	{
		printf("bash: %d: command not found\n", g_signal);
		g_signal = 127;
		return (1);
	}
	return (0);
}

void	regular_cmd(t_data *data, int *i)
{
	int	is_last_cmd;

	while (data->cmds[*i] && data->cmds[0] != NULL)
	{
		is_last_cmd = ((*i) == data->n_pipe);
		ft_init_exe(data, is_last_cmd);
		ft_parent(data, data->cmds[*i]);
		(*i)++;
	}
}

int	handle_redir_output_special(t_data *data, int saved_stdout, int j)
{
	if (ft_strcmp(data->cmds[0][j], ">") == 0 && data->cmds[0][j + 1])
	{
		if (data->cmds[0][j + 1] != NULL)
		{
			redirect_output(data->cmds[0][j + 1]);
			free(data->cmds[0][j]);
			data->cmds[0][j] = NULL;
			free(data->cmds[0][j + 1]);
			data->cmds[0][j + 1] = NULL;
			ft_exec_builtin(data, data->cmds[0]);
			if (dup2(saved_stdout, STDOUT_FILENO) == -1)
			{
				perror("dup2 restore");
				close(saved_stdout);
				exit(EXIT_FAILURE);
			}
			close(saved_stdout);
			return (1);
		}
	}
	return (0);
}

int	handle_redir_append_special(t_data *data, int saved_stdout, int j)
{
	if (ft_strcmp(data->cmds[0][j], ">>") == 0 && data->cmds[0][j + 1])
	{
		if (data->cmds[0][j + 1] != NULL)
		{
			redirect_append_output(data->cmds[0][j + 1]);
			data->cmds[0][j] = NULL;
			data->cmds[0][j + 1] = NULL;
			ft_exec_builtin(data, data->cmds[0]);
			if (dup2(saved_stdout, STDOUT_FILENO) == -1)
			{
				perror("dup2 restore");
				close(saved_stdout);
				exit(EXIT_FAILURE);
			}
			close(saved_stdout);
			return (1);
		}
	}
	return (0);
}
