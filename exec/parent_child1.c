/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_child1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malanglo <malanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:29:43 by malanglo          #+#    #+#             */
/*   Updated: 2024/09/19 17:34:57 by malanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clean_child(t_data *data)
{
	if (data->line)
		free(data->line);
	if (data->tokens)
		free_double_pointer(data->tokens);
	if (data->cmds)
		free_triple_pointer(data->cmds);
	free_double_pointer(data->original_envp);
	if (data->safe_envp != NULL)
	{
		free_double_pointer(data->safe_envp);
		data->safe_envp = NULL;
	}
	free(data->exe);
}

void	ft_fork_builtin(t_data *data, char **cmd)
{
	int	ret;

	if (ft_strcmp(cmd[0], "echo") == 0)
		ret = echo_cmd(cmd);
	else if (ft_strcmp(cmd[0], "cd") == 0 || ft_strcmp(cmd[0], "~") == 0)
		ret = cd_cmd(cmd, data);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		ret = pwd_cmd();
	else if (ft_strcmp(cmd[0], "export") == 0)
		ret = export_cmd(cmd, &data->tmp_envp);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		ret = unset_cmd(cmd, &data->tmp_envp);
	else if (ft_strcmp(cmd[0], "env") == 0)
		ret = env_cmd(cmd, data->tmp_envp, data);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		ret = exit_cmd(cmd, data);
	else
		ret = 0;
	clean_child(data);
	exit(ret);
}

int	ft_get_slash(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void	free_and_set_to_null(char **cmd, int index)
{
	if (cmd[index])
	{
		free(cmd[index]);
		cmd[index] = NULL;
	}
	if (cmd[index + 1])
	{
		free(cmd[index + 1]);
		cmd[index + 1] = NULL;
	}
}

int	handle_all_redir(char **cmd, int *i, int *here_doc_fd, t_data *data)
{
	if (ft_strcmp(cmd[*i], ">") == 0 && cmd[(*i) + 1])
	{
		redirect_output(cmd[(*i) + 1]);
		free_and_set_to_null(cmd, *i);
		return (1);
	}
	else if (ft_strcmp(cmd[*i], ">>") == 0 && cmd[(*i) + 1])
	{
		redirect_append_output(cmd[(*i) + 1]);
		free_and_set_to_null(cmd, *i);
		return (1);
	}
	else if (ft_strcmp(cmd[*i], "<") == 0 && cmd[(*i) + 1])
	{
		redirect_input(cmd[(*i) + 1]);
		free_and_set_to_null(cmd, *i);
		return (1);
	}
	else if (ft_strcmp(cmd[*i], "<<") == 0 && cmd[(*i) + 1])
	{
		*here_doc_fd = handle_here_doc(cmd[(*i) + 1], data);
		cmd[*i] = NULL;
		return (1);
	}
	return (0);
}
