/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_var_helper1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malanglo <malanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:50:56 by malanglo          #+#    #+#             */
/*   Updated: 2024/09/14 16:10:30 by malanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*extract_variable(char *tmp_token, int i)
{
	char	*found;

	found = stock_what_comes_after_dollar(tmp_token, i);
	if (!found)
		return (NULL);
	return (found);
}

int	variable_in_envp(char *found, char **envp)
{
	if (compare_to_env_variables(envp, found) == 1)
		return (1);
	return (0);
}

char	*get_value(char *found, char **envp)
{
	char	*value;

	value = get_envp_value(envp, found);
	if (!value)
		return (NULL);
	return (value);
}

char	*replace_variable(char *tmp_token, char *value, int key_len,
		int prefix_len)
{
	char	*new_token;

	new_token = switch_key_to_value(tmp_token, value, key_len, prefix_len);
	if (!new_token)
		return (NULL);
	return (new_token);
}

char	g_n_char(char *exp_token, int prefix_len, int value_len,
		int exp_len)
{
	int	value_end_index;

	value_end_index = prefix_len + value_len;
	if (value_end_index < exp_len)
		return (exp_token[value_end_index]);
	return ('\0');
}
