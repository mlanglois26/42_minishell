/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_var_helper2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malanglo <malanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:01:00 by malanglo          #+#    #+#             */
/*   Updated: 2024/09/16 15:26:16 by malanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*ft_real(void *ptr, size_t newsize)
{
	char	*new_ptr;
	size_t	cur_size;

	if (ptr == 0)
		return (malloc(newsize));
	cur_size = sizeof(ptr);
	if (newsize <= cur_size)
		return (ptr);
	new_ptr = malloc(newsize);
	ft_memcpy(ptr, new_ptr, cur_size);
	free(ptr);
	return (new_ptr);
}

char	*realloc_token(char *exp_token, char *tmp_token, int prefix_len)
{
	char	*new_token;

	new_token = ft_real(exp_token, sizeof(char) * (prefix_len + 1));
	if (!new_token)
		return (NULL);
	ft_strncpy(new_token, tmp_token, prefix_len);
	new_token[prefix_len] = '\0';
	return (new_token);
}

void	free_everything(char *found, char *value, char *tmp_token)
{
	free(found);
	free(value);
	free(tmp_token);
}

char	*handle_next_char(char *exp_token, char *tmp_token, char next_char,
		int prefix_len)
{
	if (next_char != '\0' && next_char != '"' && next_char != '\'')
	{
		exp_token = realloc_token(exp_token, tmp_token, prefix_len);
		if (!exp_token)
			return (NULL);
	}
	return (exp_token);
}

char	*replace_var_in_token_logic(char *tmp_token, int i, char **envp)
{
	char	*found;
	char	*value;
	char	*exp_token;

	found = extract_variable(tmp_token, i);
	if (!found)
		return (NULL);
	value = get_value(found, envp);
	int (key_len) = get_key_len(envp, found);
	int (prefix_len) = len_of_what_comes_before_dollar(tmp_token, i);
	exp_token = replace_variable(tmp_token, value, key_len, prefix_len);
	if (exp_token == NULL)
		return (free(found), NULL);
	int (exp_len) = ft_strlen(exp_token);
	if (!variable_in_envp(found, envp))
		return (free(found), tmp_token);
	if (!value)
		return (free(found), tmp_token);
	char (next_char) = g_n_char(exp_token, prefix_len, strlen(value), exp_len);
	exp_token = handle_next_char(exp_token, tmp_token, next_char, prefix_len);
	if (!exp_token)
		return (free(found), NULL);
	free_everything(found, value, tmp_token);
	return (exp_token);
}
