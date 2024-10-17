/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5-parse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malanglo <malanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:50:38 by malanglo          #+#    #+#             */
/*   Updated: 2024/09/19 16:36:45 by malanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	process_line(t_data *data)
{
	data->line = readline("\033[1;4;92m🐈 Marie-shell 🐈$\033[0m ");
	if (data->line == NULL)
	{
		data->eof_flag = 1;
		return ;
	}
	if (*data->line != '\0')
		add_history(data->line);
}

char	**split_line_according_to_quotes(char *line)
{
	char	**tokens;

	tokens = get_token_array(line);
	if (!tokens)
	{
		free(line);
		return (NULL);
	}
	return (tokens);
}

void	prepare_tokens(t_data *data)
{
	if (all_operators_are_inside_quotes(data->line) == 0)
		data->line = modify_line(data->line);
	data->tokens = split_line_according_to_quotes(data->line);
}

void	handle_tokens(t_data *data)
{
	if (handle_quotes_count(data->tokens, data->line) == 0)
	{
		data->skip_token_processing = 1;
		return ;
	}
	if (!data->tokens)
	{
		data->skip_token_processing = 1;
		return ;
	}
	if (dollar_found_in_array(data->tokens) == 1)
		go_to_expander(data->tokens, &data->tmp_envp);
	if (quotes_must_be_deleted(data->tokens) == 1)
		data->tokens = return_tokens_without_quotes(data->tokens);
	if (data->tokens[0] != NULL && ft_strcmp(data->tokens[0], "|") == 0)
		printf("bash: syntax error near unexpected token `%s'\n",
			data->tokens[0]);
	if (data->tokens[0] != NULL && ft_strcmp(data->tokens[0], "/") == 0)
	{
		printf("bash: %s: Is a directory\n", data->tokens[0]);
		free(data->line);
		free_double_pointer(data->tokens);
		data->tokens = NULL;
	}
}

void	clean_3(t_data *data)
{
	free_double_pointer(data->tmp_envp);
	free_double_pointer(data->original_envp);
	free(data->exe);
}
