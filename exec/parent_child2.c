/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_child2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malanglo <malanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:01:42 by malanglo          #+#    #+#             */
/*   Updated: 2024/09/19 17:35:17 by malanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_child(t_data *data, char **cmd)
{
	int (here_doc_fd) = -1;
	int (i) = 0;
	while (cmd[i])
	{
		if (handle_all_redir(cmd, &i, &here_doc_fd, data) == 1)
			break ;
		i++;
	}
	if (here_doc_fd != -1)
	{
		if (dup2(here_doc_fd, STDIN_FILENO) == -1)
		{
			perror("Erreur de dup2 pour here_doc");
			close(here_doc_fd);
			exit(1);
		}
		close(here_doc_fd);
	}
	if (ft_is_builtin(cmd[0]))
		ft_fork_builtin(data, cmd);
	else if (cmd[0] != NULL && ft_get_slash(cmd[0]))
		ft_absolute_cmd(cmd, data->tmp_envp, data);
	else
		ft_execute_command(cmd, data);
}

void	ft_parent_heart(t_data *data)
{
	if (data->exe->fd_in != -1)
	{
		dup2(data->exe->fd_in, STDIN_FILENO);
		close(data->exe->fd_in);
	}
	if (data->n_pipe > 0)
		dup2(data->exe->pipe_fd[1], STDOUT_FILENO);
	if (data->exe->pipe_fd[0] != -1)
	{
		close(data->exe->pipe_fd[0]);
		data->exe->pipe_fd[0] = -1;
	}
	if (data->exe->pipe_fd[1] != -1)
	{
		close(data->exe->pipe_fd[1]);
		data->exe->pipe_fd[1] = -1;
	}
}

void	ft_parent(t_data *data, char **cmd)
{
	signal_handler_child();
	if (data->exe->pid == 0)
	{
		ft_parent_heart(data);
		ft_child(data, cmd);
		exit(0);
	}
	else
	{
		if (data->exe->pipe_fd[1] != -1)
			close(data->exe->pipe_fd[1]);
		if (data->exe->fd_in != -1)
			close(data->exe->fd_in);
		data->exe->fd_in = data->exe->pipe_fd[0];
	}
}
