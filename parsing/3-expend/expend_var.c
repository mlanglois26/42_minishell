/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malanglo <malanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 12:34:14 by malanglo          #+#    #+#             */
/*   Updated: 2024/09/16 14:37:34 by malanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*switch_key_to_value(char *tmp_token, char *value, int key_len,
		int prefix_len)
{
	char	*exp_tmp_token;
	int		new_len;
	char	*suffix_start;

	if (value && tmp_token)
		new_len = ft_strlen(tmp_token) - key_len + ft_strlen(value) - 1;
	else
		return (NULL);
	exp_tmp_token = malloc(sizeof(char) * (new_len + 1));
	if (!exp_tmp_token)
		return (NULL);
	exp_tmp_token[0] = '\0';
	if (prefix_len > 0)
		ft_strncat(exp_tmp_token, tmp_token, prefix_len);
	ft_strncat(exp_tmp_token, value, ft_strlen(value));
	suffix_start = tmp_token + prefix_len + key_len + 1;
	if (ft_strlen(suffix_start) != 0)
		ft_strcat(exp_tmp_token, suffix_start);
	return (exp_tmp_token);
}

static char	*replace_var_in_token(char *token, char **envp)
{
	char	*tmp_token;
	char	*new_token;
	int		len;

	int (i) = 0;
	tmp_token = ft_strdup(token);
	if (!tmp_token)
		return (NULL);
	len = ft_strlen(tmp_token);
	while (i < len)
	{
		if (tmp_token[i] == '$'
			&& this_dollar_is_inside_single_quotes_improved(tmp_token, i) == 0)
		{
			new_token = replace_var_in_token_logic(tmp_token, i, envp);
			if (!new_token)
				return (free(tmp_token), NULL);
			tmp_token = new_token;
			len = ft_strlen(tmp_token);
		}
		i++;
	}
	return (tmp_token);
}

void	remove_token(char **tokens, int i)
{
	int	j;

	j = i;
	while (tokens[j] != NULL)
	{
		tokens[j] = tokens[j + 1];
		j++;
	}
}

void	handle_expansion(char **tokens, char *expanded_token, int i)
{
	if (expanded_token == NULL || strlen(expanded_token) == 0)
	{
		remove_token(tokens, i);
		free(expanded_token);
	}
	else
		tokens[i] = expanded_token;
}

void	go_to_expander(char **tokens, char ***envp)
{
	int		i;
	char	*expanded_token;

	i = 0;
	while (tokens[i] != NULL)
	{
		expanded_token = replace_var_in_token(tokens[i], *envp);
		if (expanded_token == NULL)
		{
			return ;
		}
		free(tokens[i]);
		handle_expansion(tokens, expanded_token, i);
		if (tokens[i] != NULL)
			i++;
	}
}
