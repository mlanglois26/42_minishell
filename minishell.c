/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malanglo <malanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 11:59:18 by malanglo          #+#    #+#             */
/*   Updated: 2024/09/19 17:42:41 by malanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_signal;

void	init_all_flags(t_data *data)
{
	data->env_null = 0;
	data->path_flag = 0;
	data->path_must_be_hidden = 0;
	data->is_exported_flag = 0;
	data->code_error = 0;
	data->eof_flag = 0;
	data->home_flag = 0;
	data->oldpwd_flag = 0;
	data->skip_token_processing = 0;
	data->redir_signal = 0;
}

t_data	init_data(char **envp)
{
	t_data	data;

	data.line = NULL;
	data.tokens = NULL;
	data.cmds = NULL;
	data.original_envp = get_dup_env(envp);
	data.tmp_envp = get_dup_env(envp);
	data.safe_envp = NULL;
	data.child_pid = 0;
	data.n_pipe = 0;
	data.exe = malloc(sizeof(t_exe));
	if (!data.exe)
		exit(1);
	data.exe->pipe_fd[0] = -1;
	data.exe->pipe_fd[1] = -1;
	data.exe->pid = -1;
	data.exe->stat_log = 0;
	data.exe->fd_in = 0;
	data.exe->fd_out = 1;
	data.exe->n_fork = 0;
	init_all_flags(&data);
	return (data);
}

int	parse(t_data *data)
{
	signal_handler_parent();
	init_ctrl_c(data);
	process_line(data);
	if (data->eof_flag)
		return (1);
	prepare_tokens(data);
	handle_tokens(data);
	if (data->skip_token_processing == 1)
	{
		data->skip_token_processing = 0;
		return (1);
	}
	return (0);
}

void	ft_exec(t_data *data)
{
	int	i;
	int	saved_stdout;

	i = 0;
	saved_stdout = dup(STDOUT_FILENO);
	if (data->path_flag == 1)
		unset_without_env(data);
	data->n_pipe = count_cmds(data) - 1;
	data->exe->fd_in = -1;
	if (data->cmds != NULL && data->cmds[0] != NULL)
	{
		if (cmd_special(data) == 1)
			return ;
		if (!data->n_pipe && ft_is_builtin(data->cmds[0][0]))
		{
			if (builtin_cmd(data, saved_stdout))
				return ;
			ft_exec_builtin(data, data->cmds[0]);
			return ;
		}
		regular_cmd(data, &i);
	}
	handle_code_error(data);
}

int	main(int argc, char **argv, char **envp)
{
	int		running;
	t_data	data;

	(void)argv;
	if (argc != 1)
	{
		printf("usage: ./minishell\n");
		return (0);
	}
	init_and_configure_data(&data, envp);
	while (!data.eof_flag)
	{
		running = parse(&data);
		if (running == 1)
			continue ;
		data.cmds = create_cmds_array(data.tokens);
		if (data.cmds[0][0] != NULL)
			ft_exec(&data);
		clean_1(&data);
	}
	if (data.path_flag == 0)
		clean_2(&data);
	else
		clean_3(&data);
	return (0);
}
