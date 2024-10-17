/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malanglo <malanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 10:32:56 by malanglo          #+#    #+#             */
/*   Updated: 2024/09/17 11:47:04 by malanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	ft_copy_str(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	global_len;
	char	*new_str;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	global_len = s1_len + s2_len + 1;
	new_str = (char *)malloc(global_len * sizeof(char));
	if (!new_str)
		return (NULL);
	ft_copy_str(new_str, s1, s1_len);
	ft_copy_str(new_str + s1_len, s2, s2_len);
	new_str[s1_len + s2_len] = '\0';
	return (new_str);
}

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*c_src;
	char	*c_dest;
	size_t	i;

	if (dest == 0 && src == 0)
		return (NULL);
	c_src = (char *)src;
	c_dest = (char *)dest;
	i = 0;
	while (n > i)
	{
		c_dest[i] = c_src[i];
		i++;
	}
	return (dest);
}
